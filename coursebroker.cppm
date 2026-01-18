module;

#include <pqxx/pqxx>
#include <pqxx/zview>
#include <pqxx/params>

export module registrar:broker.coursebroker;
import :broker.registrarbroker;

import :domain.course;

import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::vector;

export class CourseBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<class Course> findCourseById(const std::string& id);

    bool CourseEvalueAccess(const string& cid,const string& tid);
    void initialize();

private:
    vector<std::shared_ptr<class Course>> _courses;
    shared_ptr<class Course> findCourseByIdLocal(const string &id);
    shared_ptr<class Course> findCourseByIdDB(const string& id);
};

void CourseBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = t.exec(pqxx::zview{"SELECT cno,cname,ccredit,cacademy,tno FROM course LIMIT 5"}); //只读入前5行进入缓存
    t.commit();
    _courses.clear();
    for(const auto& row : res) {
        _courses.push_back(std::make_shared<Course>(
            res[0]["cno"].as<string>(),
            res[0]["cname"].as<string>(),
            res[0]["ccredit"].as<string>(),
            res[0]["cacademy"].as<string>(),
            res[0]["tno"].as<string>()));
    }
}

bool CourseBroker::CourseEvalueAccess(const string& cid,const string& tid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        pqxx::result res = t.exec(pqxx::zview{"SELECT EXISTS(SELECT 1 FROM course WHERE cno = $1 AND tno = $2)"},pqxx::params{cid,tid});
        t.commit();
        if(res.size() == 1){
            return res[0][0].as<bool>();
        }
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
    return false;
}



shared_ptr<Course> CourseBroker::findCourseById(const std::string& id)
{
    if(auto local = findCourseByIdLocal(id))  //先从本地缓存中找
        return local;
    return findCourseByIdDB(id); //没有就去数据库中找
}

shared_ptr<Course> CourseBroker::findCourseByIdLocal(const string &id)
{
    for(auto& course : _courses){
        if(course->hasId(id))
            return course;
    }
    return nullptr;
}

shared_ptr<Course> CourseBroker::findCourseByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"SELECT cno,cname,ccredit,cacademy,tno FROM course WHERE cno = $1"},pqxx::params{id});
        t.commit();
        if (res.empty()) {
            std::cout << "未找到课程ID：" << id << endl;
            return nullptr;
        }
        auto course = std::make_shared<Course>(
            res[0]["cno"].as<string>(),
            res[0]["cname"].as<string>(),
            res[0]["ccredit"].as<string>(),
            res[0]["cacademy"].as<string>(),
            res[0]["tno"].as<string>());
        _courses.push_back(std::move(course));   //把用到的存入缓存区
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
