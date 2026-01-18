module;

#include <pqxx/pqxx>

export module registrar:broker.enrollmentbroker;
import :broker.registrarbroker;

import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;

export class EnrollmentBroker : public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<Enrollment> findEnrollmentById(const string& sid,const string& cid);
//    string getCourseRoster(const string& courseId);

    bool save(const string& sid,const string& cid);
    bool remove(const string& sid,const string& cid)

    bool updateGrade(const Enrollment& enrollment);

    void initialize();

private:
    vector<std::shared_ptr<Enrollment>> _enrollment;
    shared_ptr<Erollment> findEnrollmentByIdLocal(const string& sid,const string& cid);
    shared_ptr<Erollment> findEnrollBymentIdDB(const string& sid,const string& cid);
};

void EnrollmentBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::work t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT sno,cno,grade FROM sc LIMIT 5"); //只读入前5行进入缓存
    rtx.commit();
    _enrollment.clear();
    for(const auto& row : res) {
        string sno = res[0]["sno"].as<string>();
        string cno = res[0]["cno"].as<string>();

        if(!row["grade"].is_null()){
            double grade = res[0]["grade"].as<double>();
            auto e = std::make_shared<Enrollment>(sno,cno,grade);
            _enrollment.push_back(e);
        }else{
            auto en = std::make_shared<Enrollment>(sno,cno,0.0)
            _enrollment.push_back(en);
        }
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
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM sc WHERE Sno = $1 AND Cno = $2)",sid,cid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (!exists) {
            pqxx::work deleteTxn(*dbConnection);
            string saveSql = "INSERT INTO sc VALUES ($1,$2)";
            deleteTxn.exec_params(saveSql,sid,cid);
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
    if (!enrollment) {
        cerr << "Enrollment对象为空" << endl;
        return false;
      }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM sc WHERE Sno = $1 AND Cno = $2)",sid,cid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            string deleteSql = "DELETE FROM sc WHERE Sno = $1 AND Cno = $2";
            deleteTxn.exec_params(deleteSql,sid,cid);
            deleteTxn.commit();

            for (auto it = _enrollment.begin(); it != _enrollment.end(); ) {
                if ((*it)->sid == sid && (*it)->cid == cid) {
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
        return nullptr;
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
        auto res = t.exec_params("UPDATE sc SET grade = $1 WHERE sno = $2 AND cno = $3",enrollment._grade.m_grade,
                                 enrollment._sid,enrollment._cid);
        t.commit();
        return true;
    } catch (const std::exception& e) {
        cerr << "更新成绩失败：" << e.what() << endl;
        return false;
    }
}


shared_ptr<Enrollment> EnrollmentBroker::findEnrollmentById(const std::string& sid,const std::string& cid)
{
    if(auto local = findCourseByIdLocal(id))  //先从本地缓存中找
        return local;
    return findCourseByIdDB(id); //没有就去数据库中找
}

shared_ptr<Erollment> EnrollmentBroker::findEnrollmentByLocal(const string& sid,const string& cid)
{
    for(auto& enrollment : _enrollment){
        if(enrollment->hasId(id))
            return enrollment;
    }
    return nullptr;
}

shared_ptr<Enrollment> EnrollmentBroker::findEnrollBymentIdDB(const string& sid,const string& cid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT sno,cno,grade FROM course WHERE cno = $1",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到scID：" << id << endl;
            return nullptr;
        }
        string sno = res[0]["sno"].as<string>();
        string cno = res[0]["cno"].as<string>();

        if(!row["grade"].is_null()){
            double grade = res[0]["grade"].as<double>();
            _enrollment.push_back(std::make_shared<Enrollment>(sno,cno,grade));
        }else{
            _enrollment.push_back(std::make_shared<Enrollment>(sno,cno,0.0));
        }
        _enrollment.push_back(std::move(Enrollment));   //把用到的存入缓存区
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}
