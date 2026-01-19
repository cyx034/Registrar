export module registrar:domain.schedule;
import std;

using std::vector;
using std::weak_ptr;
using std::string;
using std::shared_ptr;
using std::print;

//课程表
export class Schedule
{
    friend class ScheduleBroker;
public:
    Schedule(string scheduleid,string term,string academy,string major,string gradelevel);
    ~Schedule();
    shared_ptr<Schedule> create(string scheduleid,string term,string academy,string major,string gradelevel);
    void addScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry);
    void removeScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry);
    bool hasId(string id);
private:
    string m_scheduleid;
    string m_term;
    string m_academy;
    string m_major;
    string m_gradelevel;
    vector<shared_ptr<class ScheduleEntry>> _scheduleEntrys;
};

Schedule::Schedule(string scheduleid,string term,string academy,string major,string gradelevel)
    :m_scheduleid(scheduleid),m_term(term),m_academy(academy),m_major(major),m_gradelevel(gradelevel)
{}

Schedule::~Schedule()
{}

//创建新的课程表
shared_ptr<Schedule> Schedule::create(string scheduleid,string term,string academy,string major,string gradelevel)
{
    return make_shared<Schedule>(scheduleid,term,academy,major,gradelevel);
}

//向课程表中添加新的课程条目
void Schedule::addScheduleEntry(shared_ptr<ScheduleEntry> scheduleEntry)
{
    _scheduleEntrys.push_back(scheduleEntry);
    print("已从该课程中成功添加该条目");
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

bool Schedule::hasId(string id)
{
    return m_scheduleid == id;
}
