module;

#include <pqxx/pqxx>

export module registrar:broker.schedulebroker;
import :broker.registrarbroker;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;

export class ScheduleBroker: public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    std::shared_ptr<Schedule> findScheduleById(const std::string& id);
    void initialize();

private:
    vector<shared_ptr<Schedule>> _schedule;
    shared_ptr<Schedule> findScheduleByIdLocal(const string &id);
    shared_ptr<Schedule> findScheduleByIdDB(const string& id);
};

void ScheduleBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT scheduleid,term,acadamy,major,gradelevel FROM schedule LIMIT 5");
    rtx.commit();
    _schedule.clear();
    for(const auto& row : res) {
        _schedule.push_back(std::make_shared<Schedule>(
            res[0]["scheduleid"].as<string>(),
            res[0]["term"].as<string>(),
            res[0]["academy"].as<string>(),
            res[0]["major"].as<string>()
            res[0]["gradelevel"].as<string>()));
    }
}

shared_ptr<Schedule> ScheduleBroker::save(const string& scid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM sc WHERE scheduleid = $1)",scid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (!exists) {
            pqxx::work deleteTxn(*dbConnection);
            string saveSql = "INSERT INTO sc VALUES $1";
            deleteTxn.exec_params(saveSql,scid);
            deleteTxn.commit();

            auto schedule = std::make_shared<Schedule>(scid,);
            _schedule.push_back(schedule);  //存入缓存区

            std::print("注册成功\n");
            return schedule;
        } else {
            std::print("已注册该课程\n");
            return nullptr;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}





shared_ptr<Schedule> ScheduleBroker::findScheduleById(const std::string& id)
{
    if(auto local = findScheduleByIdLocal(id))  //先从本地缓存中找
        return local;
    return findScheduleByIdDB(id); //没有就去数据库中找
}

shared_ptr<Schedule> ScheduleBroker::findScheduleByIdLocal(const string &id)
{
    for(auto& schedule : _schedule){
        if(schedule->hasId(id))
            return schedule;
    }
    return nullptr;
}

shared_ptr<Schedule> ScheduleBroker::findScheduleByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT scheduleid,term,acadamy,major,gradelevel FROM schedule WHERE scheduleid = $1",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到课程表id：" << id << endl;
            return nullptr;
        }
        auto schedule = std::make_shared<Schedule>(
            res[0]["scheduleid"].as<string>(),
            res[0]["term"].as<string>(),
            res[0]["academy"].as<string>(),
            res[0]["major"].as<string>()
            res[0]["gradelevel"].as<string>()
        );
        _schedule.push_back(std::move(schedule));
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}

