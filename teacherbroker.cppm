module;

#include <pqxx/pqxx>

export module registrar:broker.teacherbroker;
import :broker.registrarbroker;

import std;

using std::string;
using std::cerr;
using std::endl;
using std::unique_ptr;

export class TeacherBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::unique_ptr<Teacher> findTeacherById(const std::string& id);
    void initialize();

private:
    vector<std::unique_ptr<Teacher>> _teacher;
    unique_ptr<Teacher> findTeacherByIdLocal(const string &id);
    unique_ptr<Teacher> findTeacherByIdDB(const string& id);
};

void TeacherBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT tno,tname,tacademy FROM teacher LIMIT 5;"); //只读入前5行进入缓存
    rtx.commit();
    _teacher.clear();
    for(const auto& row : res) {
        _teacher.push_back(std::make_unique<Teacher>(
            res[0]["tno"].as<string>(),
            res[0]["tname"].as<string>(),
            res[0]["tacademy"].as<string>()));
    }
}

unique_ptr<Teacher> TeacherBroker::findTeacherById(const std::string& id)
{
    if(auto local = findTeacherByIdLocal(id))  //先从本地缓存中找
        return local;
    return findTeacherByIdDB(id); //没有就去数据库中找
}

unique_ptr<Teacher> TeacherBroker::findTeacherByIdLocal(const string &id)
{
    for(auto& teacher : _teacher){
        if(teacher->hasId(id))
            return teacher;
    }
    return nullptr;
}

unique_ptr<Teacher> TeacherBroker::findTeacherByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT tno,tname,tacademy FROM teacher WHERE tno = $1;",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到老师ID：" << id << endl;
            return nullptr;
        }
        auto teacher = std::make_unique<Teacher>(
            res[0]["tno"].as<string>(),
            res[0]["tname"].as<string>(),
            res[0]["tacademy"].as<string>());
        _teacher.pushback(std::move(teacher));   //把用到的存入缓存区
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
