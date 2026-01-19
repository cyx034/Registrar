module;

#include <pqxx/pqxx>
#include <pqxx/zview>
#include <pqxx/params>
export module registrar:broker.enrollmentbroker;
import :broker.registrarbroker;

//import :broker.coursebroker;

import :domain.enrollment;

import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::vector;


export class EnrollmentBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<class Enrollment> findEnrollmentById(const string& sid,const string& cid);
//    string getCourseRoster(const string& courseId);

    bool save(const string& sid,const string& cid);
    bool remove(const string& sid,const string& cid);

    bool updateGrade(const Enrollment& enrollment);

    void printSchedule(string sid);

    void initialize();

private:
    vector<std::shared_ptr<class Enrollment>> _enrollment;
    shared_ptr<class Enrollment> findEnrollmentByIdDB(const string& sid,const string& cid);
    shared_ptr<Enrollment> findEnrollmentByLocal(const string& sid,const string& cid);
};

void EnrollmentBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::work t(*dbConnection);
    pqxx::result res = t.exec(pqxx::zview{"SELECT sno,cno,grade FROM sc LIMIT 5"}); //只读入前5行进入缓存
    t.commit();
    _enrollment.clear();
    for(const auto& row : res) {
        string sno = row["sno"].as<string>();
        string cno = row["cno"].as<string>();

        if(!row["grade"].is_null()){
            double grade = row["grade"].as<double>();
            auto e = std::make_shared<Enrollment>(sno,cno,grade);
            _enrollment.push_back(e);
        }else{
            auto en = std::make_shared<Enrollment>(sno,cno,0.0);
            _enrollment.push_back(en);
        }
    }
}

void EnrollmentBroker::printSchedule(string sid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::work t(*dbConnection);
    pqxx::result res = t.exec(pqxx::zview{"SELECT sc.cno,course.cname,course.ccredit,course.cacademy,teacher.tname FROM sc "
                                          "JOIN course ON sc.cno = course.cno JOIN teacher ON teacher.tno = course.tno WHERE sno = $1"},pqxx::params{sid});
    t.commit();
    for(const auto& row : res) {
        std::print("id      name               credit        academy                teacher\n");
        std::print(" {:<8} ",row["cno"].as<string>());
        std::print(" {:<20} ",row["cname"].as<string>());
        std::print(" {:<5} ",row["ccredit"].as<string>());
        std::print(" {:<20}         ",row["cacademy"].as<string>());
        std::print(" {}\n",row["tname"].as<string>());
    }
}



bool EnrollmentBroker::save(const string& sid,const string& cid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"SELECT EXISTS(SELECT 1 FROM sc WHERE Sno = $1 AND Cno = $2)"},pqxx::params{sid,cid});
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (!exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec(pqxx::zview{"INSERT INTO sc VALUES ($1,$2)"},pqxx::params{sid,cid});
            deleteTxn.commit();

            auto enrollment = std::make_shared<Enrollment>(sid,cid,0.0);
            _enrollment.push_back(enrollment);  //存入缓存区

            std::print("注册成功\n");
            return true;
        } else {
            std::print("已注册该课程\n");
            return true;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool EnrollmentBroker::remove(const string& sid,const string& cid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"SELECT EXISTS(SELECT 1 FROM sc WHERE Sno = $1 AND Cno = $2)"},pqxx::params{sid,cid});
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);

            deleteTxn.exec(pqxx::zview{"DELETE FROM sc WHERE Sno = $1 AND Cno = $2"},pqxx::params{sid,cid});
            deleteTxn.commit();

            for (auto it = _enrollment.begin(); it != _enrollment.end(); ) {
                if ((*it)->_sid == sid && (*it)->_cid == cid) {
                    it = _enrollment.erase(it);  // erase返回下一个有效迭代器
                } else {
                    ++it;
                }
            }

            std::print("删除成功\n");
            return true;
        } else {
            std::print("未注册该课程\n");
            return true;
        }
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool EnrollmentBroker::updateGrade(const Enrollment& enrollment)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"UPDATE sc SET grade = $1 WHERE sno = $2 AND cno = $3"},pqxx::params{enrollment._grade.m_grade,
                                 enrollment._sid,enrollment._cid});
        t.commit();
        return true;
    } catch (const std::exception& e) {
        cerr << "更新成绩失败：" << e.what() << endl;
        return false;
    }
}


shared_ptr<Enrollment> EnrollmentBroker::findEnrollmentById(const std::string& sid,const std::string& cid)
{
    if(auto local = findEnrollmentByLocal(sid,cid))//先从本地缓存中找
        return local;
    return findEnrollmentByIdDB(sid,cid); //没有就去数据库中找
}

shared_ptr<Enrollment> EnrollmentBroker::findEnrollmentByLocal(const string& sid,const string& cid)
{
    for(auto& enrollment : _enrollment){
        if(enrollment->hasId(sid,cid))
            return enrollment;
    }
    return nullptr;
}

shared_ptr<Enrollment> EnrollmentBroker::findEnrollmentByIdDB(const string& sid,const string& cid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        pqxx::result res = t.exec(pqxx::zview{"SELECT sno,cno,grade FROM sc WHERE sno = $1 AND cno = $2"},pqxx::params{sid,cid});
        t.commit();
        if (res.empty()) {
            std::print("未找到scID：\n");
            return nullptr;
        }
        pqxx::row row = res[0];
        string sno = res[0]["sno"].as<string>();
        string cno = res[0]["cno"].as<string>();

        shared_ptr<Enrollment> enrollment;
        if(!row["grade"].is_null()){
            double grade = res[0]["grade"].as<double>();
            enrollment = std::make_shared<Enrollment>(sno,cno,grade);
            _enrollment.push_back(enrollment);
        }else{
            enrollment = std::make_shared<Enrollment>(sno,cno,0.0);
            _enrollment.push_back(enrollment);
        }
        return enrollment;
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
