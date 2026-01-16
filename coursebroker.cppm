module;

#include <pqxx/pqxx>

export module coursebroker;

import std;

using std::string;
using std::cerr;
using std::endl;
using std::course;

export class CourseBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::unique_ptr<Course> findCourseById(const std::string& id);
    void initialize();

private:
    vector<std::unique_ptr<Course>> _courses;
    unique_ptr<Course> findCourseByIdLocal(const string &id);
    unique_ptr<Course> findCourseByIdDB(const string& id);
};

void CourseBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT cno,cname,ccredit,cacademy,tno FROM student");
    rtx.commit();
    _courses.clear();
    for(const auto& row : res) {
        _courses.push_back(std::make_unique<Student>(
            res[0]["cno"].as<string>(),
            res[0]["cname"].as<string>(),
            res[0]["ccredit"].as<string>(),
            res[0]["cacademy"].as<string>(),
            res[0]["tno"].as<string>()));
    }
}

unique_ptr<Course> CourseBroker::findCourseById(const std::string& id)
{
    if(auto local = findCourseByIdLocal(id))  //先从本地缓存中找
        return local;
    return findCourseByIdDB(id); //没有就去数据库中找
}

unique_ptr<Course> CourseBroker::findCourseByIdLocal(const string &id)
{
    for(auto& student : _courses){
        if(student->hasId(id))
            return student;
    }
    return nullptr;
}

unique_ptr<Course> CourseBroker::findCourseByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT cno,cname,ccredit,cacademy,tno FROM student WHERE sid = $1",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到学生ID：" << id << endl;
            return nullptr;
        }
        auto course = std::make_unique<Course>(
            res[0]["cno"].as<string>(),
            res[0]["cname"].as<string>(),
            res[0]["ccredit"].as<string>(),
            res[0]["cacademy"].as<string>(),
            res[0]["tno"].as<string>());
        _courses.pushback(std::move(course));
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
