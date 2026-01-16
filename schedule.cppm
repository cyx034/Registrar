export module registrar:domain.schedule;
import std;
<<<<<<< Updated upstream
using std::vector;
using std::weak_ptr;
using std::string;
using std::shared_ptr;
using std::print;
=======
using std::vector;using std::weak_ptr;using std::string;using std::shared_ptr;using std::print;
>>>>>>> Stashed changes

//课程表
export class Schedule
{
public:
    Schedule(string id);
    ~Schedule();
    bool hasId(string id);
    void modify(string id);
    void addScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry);
    void removeScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry);
private:
    string m_id;
    string m_academy;
    string gradelevel;
    vector<shared_ptr<class ScheduleEntry>> _scheduleEntrys;
};

Schedule::Schedule(string id)
    :m_id(id)
{
    print("The Schedule create");
}

Schedule::~Schedule()
{}

bool Schedule::hasId(string id)
{
    return id==m_id;//判断是否有该条目id
}

//修改课程表信息
void Schedule::modify(string id)
{}

//向课程表中添加新的课程条目
void Schedule::addScheduleEntry(shared_ptr<ScheduleEntry> scheduleEntry)
{
<<<<<<< Updated upstream
    shared_ptr<ScheduleEntry> entry;
    entry->addinformation();
    this->_scheduleEntrys.push_back(entry);
    print("已成功添加该课程条目");
=======
    _scheduleEntrys.push_back(scheduleEntry);
    print("已从该课程中成功添加该条目");
>>>>>>> Stashed changes
}

//向课程表中删除课程条目
void Schedule::removeScheduleEntry(shared_ptr<ScheduleEntry> scheduleEntry)
{
    auto it = std::find(_scheduleEntrys.begin(),_scheduleEntrys.end(),scheduleEntry);
    if(it!=_scheduleEntrys.end()){
        _scheduleEntrys.erase(it);
        print("已从该课程中成功删除该条目");
    }
}
