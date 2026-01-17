module;

#include <pqxx/pqxx>

export module registrar:broker.scheduleEntrybroker;
import :broker.registrarbroker;
import std;

using std::string;
using std::cerr;
using std::endl;
using std::shared_ptr;

export class ScheduleEntryBroker: public RegistrarBroker
{
public:
    using RegistrarBroker::RegistrarBroker;

    bool save(string entryid,string sid,string cid,string classTime,string classRoom);
    bool remove(string entryid);
    bool addToSchedule(string entryid,string scheduleid);
    bool removeToSchedule(string entryid,string scheduleid);

    bool modifyEntrytime(string entryid,string time);
    bool modifyEntryroom(string entryid,string room);
    bool modifyEntryteacher(string entryid,string tid);

    std::shared_ptr<ScheduleEntry> findScheduleEntryById(const std::string& id);
    void initialize();

private:
    vector<shared_ptr<ScheduleEntry>> _scheduleEntry;
    shared_ptr<ScheduleEntry> findScheduleEntryByIdLocal(const string &id);
    shared_ptr<ScheduleEntry> findScheduleEntryByIdDB(const string& id);
};

void ScheduleEntryBroker::initialize()
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return;
    }
    pqxx::read_transaction t(*dbConnection);
    pqxx::result res = rtx.exec("SELECT entryid,scheduleid,cno,tno,time,classroom FROM schedule_entry LIMIT 5");
    rtx.commit();
    _scheduleEntry.clear();
    for(const auto& row : res) {
        _scheduleEntry.push_back(std::make_shared<StudentEntry>(
            res[0]["entryid"].as<string>(),
            res[0]["scheduleid"].as<string>(),
            res[0]["cno"].as<string>(),
            res[0]["tno"].as<string>()
            res[0]["time"].as<string>()
            res[0]["classrom"].as<string>()));
    }
}

bool ScheduleEntryBroker::modifyEntrytime(string entryid,string time)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec_params("UPDATE schedule_entry SET time = $1 WHERE entryid = $2",time,entryid);
            deleteTxn.commit();

            std::print("修改时间成功\n");
            return true;
        } else {
            std::print("没有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool ScheduleEntryBroker::modifyEntryroom(string entryid,string room)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec_params("UPDATE schedule_entry SET classroom = $1 WHERE entryid = $2",room,entryid);
            deleteTxn.commit();

            std::print("修改教室成功\n");
            return true;
        } else {
            std::print("没有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}


bool ScheduleEntryBroker::modifyEntryteacher(string entryid,string tid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec_params("UPDATE schedule_entry SET tno = $1 WHERE entryid = $2",tid,entryid);
            deleteTxn.commit();

            std::print("修改教师成功\n");
            return true;
        } else {
            std::print("没有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}


bool ScheduleEntryBroker::addToSchedule(string entryid,string scheduleid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            deleteTxn.exec_params("UPDATE schedule_entry SET scheduleid = $1 WHERE entryid = $2",scheduleid,entryid);
            deleteTxn.commit();

            std::print("课程条目加入课程表成功\n");
            return true;
        } else {
            std::print("没有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool ScheduleEntryBroker::removeToSchedule(string entryid,string scheduleid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }
    try {
        pqxx::work checkTxn(*dbConnection);
        string checkSql =
            "SELECT EXISTS(SELECT 1 FROM schedule_entry "
            "WHERE entryid = $1 AND scheduleid = $2)";

        auto res = checkTxn.exec_params(checkSql, entryid, scheduleid);
        checkTxn.commit();

        bool belongsToSchedule = res[0][0].as<bool>();
        if (!belongsToSchedule) {
            // 条目不存在或者不属于这个课程表
            // 可以进一步检查是哪种情况
            pqxx::work checkExistsTxn(*dbConnection);
            string existsSql = "SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)";
            auto existsRes = checkExistsTxn.exec_params(existsSql, entryid);
            checkExistsTxn.commit();

            bool entryExists = existsRes[0][0].as<bool>();

            if (entryExists) {
                // 条目存在，但不属于这个课程表
                cerr << "课程条目 " << entryid
                    << " 不属于课程表 " << scheduleid << endl;
            } else {
                // 条目不存在
                cerr << "课程条目 " << entryid << " 不存在" << endl;
            }
            return false;
        }
        pqxx::work deleteTxn(*dbConnection);
        string deleteSql = "UPDATE schedule_entry SET scheduleid = NULL WHERE entryid = $1";
        deleteTxn.exec_params(deleteSql, entryid);
        deleteTxn.commit();

        print("课程条目成功从课程表中删除\n")
        return true;

    } catch (const std::exception& e) {
        cerr << "操作失败: " << e.what() << endl;
        return false;
    }
}


bool ScheduleEntryBroker::save(string entryid,string sid,string cid,string classTime,string classRoom)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (!exists) {
            pqxx::work deleteTxn(*dbConnection);
            string saveSql = "INSERT INTO schedule_entry(entryid,cno,tno,time,classroom) VALUES ($1,$2,$3,$4,$5)";
            deleteTxn.exec_params(saveSql,entryid,sid,cid,classTime,classRoom);
            deleteTxn.commit();

            auto scheduleEntry = std::make_shared<ScheduleEntry>(entryid,classTime,classRoom,teacher,course);
            _scheduleEntry.push_back(scheduleEntry);  //存入缓存区

            std::print("加入课程条目成功\n");
            return true;
        } else {
            std::print("已有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}

bool ScheduleEntryBroker::remove(string entryid)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return false;
    }

    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT EXISTS(SELECT 1 FROM schedule_entry WHERE entryid = $1)",entryid);
        t.commit();
        bool exists = res[0][0].as<bool>();
        if (exists) {
            pqxx::work deleteTxn(*dbConnection);
            string deleteSql = "DELETE FROM schedule_entry WHERE entryid = $1";
            deleteTxn.exec_params(deleteSql,entry);
            deleteTxn.commit();

            for (auto it = _scheduleEntry.begin(); it != _scheduleEntry.end(); ) {
                if ((*it)->m_id == entryid) {
                    it = _scheduleEntry.erase(it);  // erase返回下一个有效迭代器
                } else {
                    ++it;
                }
            }
            std::print("删除课程条目成功\n");
            return true;
        } else {
            std::print("没有该课程条目\n");
            return false;
        }

    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return false;
    }
}



shared_ptr<ScheduleEntry> ScheduleEntryBroker::findScheduleEntryById(const std::string& id)
{
    if(auto local = findScheduleByIdLocal(id))  //先从本地缓存中找
        return local;
    return findScheduleByIdDB(id); //没有就去数据库中找
}

shared_ptr<ScheduleEntry> ScheduleEntryBroker::findScheduleEntryByIdLocal(const string &id)
{
    for(auto& scheduleEntry : _scheduleEntry){
        if(scheduleEntry->hasId(id))
            return scheduleEntry;
    }
    return nullptr;
}

shared_ptr<ScheduleEntry> ScheduleEntryBroker::findScheduleEntryByIdDB(const string& id)
{
    if (!status) {
        cerr << "数据库未连接" << endl;
        return nullptr;
    }
    try {
        pqxx::work t(*dbConnection);
        auto res = t.exec_params("SELECT entryid,scheduleid,cno,tno,time,classroom FROM schedule_entry WHERE entryid = $1",id);
        t.commit();
        if (res.empty()) {
            std::cout << "未找到课程表id：" << id << endl;
            return nullptr;
        }
        auto scheduleEntry = std::make_shared<ScheduleEntry>(
            res[0]["entryid"].as<string>(),
            res[0]["scheduleid"].as<string>(),
            res[0]["cno"].as<string>(),
            res[0]["tno"].as<string>()
            res[0]["time"].as<string>()
            res[0]["classrom"].as<string>()
        );
        _scheduleEntry.push_back(std::move(scheduleEntry));
    } catch (const std::exception& e) {
        cerr << "查询失败：" << e.what() << endl;
        return nullptr;
    }
}


