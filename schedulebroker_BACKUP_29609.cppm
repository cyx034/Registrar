module;

#include <pqxx/pqxx>
#include <pqxx/zview>
#include <pqxx/params>
export module registrar:broker.schedulebroker;
import :broker.registrarbroker;

import :domain.schedule;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;
using std::vector;

export class ScheduleBroker: public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    bool save(string scheduleid,string term,string academy,string major,string gradelevel);
    bool remove(string scheduleid);

    std::shared_ptr<class Schedule> findScheduleById(const std::string& id);
    void initialize();

private:
    vector<shared_ptr<class Schedule>> _schedule;
    shared_ptr<class Schedule> findScheduleByIdLocal(const string &id);
    shared_ptr<class Schedule> findScheduleByIdDB(const string& id);
};

void ScheduleBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = t.exec("SELECT scheduleid,term,acadamy,major,gradelevel FROM schedule LIMIT 5");
    t.commit();
    _schedule.clear();
    for(const auto& row : res) {
        _schedule.push_back(std::make_shared<Schedule>(
            res[0]["scheduleid"].as<string>(),
            res[0]["term"].as<string>(),
            res[0]["academy"].as<string>(),
            res[0]["major"].as<string>(),
            res[0]["gradelevel"].as<string>()));
    }
}

bool ScheduleBroker::save(string scheduleid,string term,string academy,string major,string gradelevel)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"SELECT EXISTS(SELECT 1 FROM schedule WHERE scheduleid = $1)"},pqxx::params{scheduleid});
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (!exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec(pqxx::zview{"INSERT INTO schedule VALUES ($1,$2,$3,$4,$5)"},pqxx::params{scheduleid,term,academy,major,gradelevel});
            deleteTxn.commit();

            auto schedule = std::make_shared<Schedule>(scheduleid,term,academy,major,gradelevel);
            _schedule.push_back(schedule);  //存入缓存区

            std::print("加入课程表成功\n");
            return true;
        } else {
            std::print("已有该课程表\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool ScheduleBroker::remove(string scheduleid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec(pqxx::zview{"SELECT EXISTS(SELECT 1 FROM schedule WHERE scheduleid = $1)"},pqxx::params{scheduleid});
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec(pqxx::zview{"DELETE FROM schedule WHERE scheduleid = $1"},pqxx::params{scheduleid});
            deleteTxn.commit();

            for (auto it = _schedule.begin(); it != _schedule.end(); ) {
                if ((*it)->m_scheduleid == scheduleid) {
                    it = _schedule.erase(it);  // erase返回下一个有效迭代器
                } else {
                    ++it;
                }
            }
            std::print("删除课程表成功\n");
            return true;
        } else {
            std::print("没有该课程表\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
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
        auto res = t.exec(pqxx::zview{"SELECT scheduleid,term,acadamy,major,gradelevel FROM schedule WHERE scheduleid = $1"},pqxx::params{id});
        t.commit();
        if (res.empty()) {
            std::cout << "未找到课程表id：" << id << endl;
            return nullptr;
        }
        auto schedule = std::make_shared<Schedule>(
            res[0]["scheduleid"].as<string>(),
            res[0]["term"].as<string>(),
            res[0]["academy"].as<string>(),
            res[0]["major"].as<string>(),
            res[0]["gradelevel"].as<string>()
        );
        _schedule.push_back(std::move(schedule));
        return schedule;
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}

