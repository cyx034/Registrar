module;

#include <pqxx/pqxx>

export module registrar:broker.studentbroker;
import :broker.registrarbroker;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::vector;

export class StudentBroker: public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<class Student> findStudentById(const std::string& id);
    void initialize();

private:
    vector<shared_ptr<class Student>> _students;
    shared_ptr<class Student> findStudentByIdLocal(const string &id);
    shared_ptr<class Student> findStudentByIdDB(const string& id);
};

void StudentBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT sno,sname,sacademy,smajor FROM student LIMIT 5");
    rtx.commit();
    _students.clear();
    for(const auto& row : res) {
        _students.push_back(std::make_shared<Student>(
            res[0]["sno"].as<string>(),
            res[0]["sname"].as<string>(),
            res[0]["sacademy"].as<string>(),
            res[0]["smajor"].as<string>()));
    }
}

shared_ptr<Student> StudentBroker::findStudentById(const std::string& id)
{
    if(auto local = findStudentByIdLocal(id))  //先从本地缓存中找
        return local;
    return findStudentByIdDB(id); //没有就去数据库中找
}

shared_ptr<Student> StudentBroker::findStudentByIdLocal(const string &id)
{
    for(auto& student : _students){
        if(student->hasId(id))
            return student;
    }
    return nullptr;
}

shared_ptr<Student> StudentBroker::findStudentByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT sno,sname,sacademy,smajor FROM student WHERE sno = $1",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到学生ID：" << id << endl;
            return nullptr;
        }
        auto student = std::make_shared<Student>(
            res[0]["sno"].as<string>(),
            res[0]["sname"].as<string>(),
            res[0]["sacademy"].as<string>(),
            res[0]["smajor"].as<string>()
        );
        _students.push_back(std::move(student));
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
