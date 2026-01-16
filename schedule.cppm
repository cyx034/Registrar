export module registrar:domain.schedule;
import std;
using std::vector;using std::weak_ptr;

//课程表
export class Schedule
{
public:
    Schedule(string id);
    ~Schedule();
    bool hasId(string id);
    void addScheduleEntry();//添加课程条目
    void removeScheduleEntry(string id);//移除课程条目
    void modifyScheduleEntry(string id);//修改课程条目
private:
    string m_id;
    string m_name;
    string m_academy;
    double grade;
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

void Schedule::addScheduleEntry()
{
    auto entry=make_shared<ScheduleEntry>;
    entry->addinformation()
    this._scheduleEntrys.push_back(entry);
    print("已成功添加该课程条目");
}

void Schedule::removeScheduleEntry(string id)
{
    for(auto& s:_scheduleEntrys){
        if(s->hasId(id)){
            _scheduleEntrys.erase(s);
            print("已成功删除该条目");
            return;
        }
    }
    print("不存在此课程条目");
}

void Schedule::modifyScheduleEntry(string id)
{
    for(auto& s:_scheduleEntrys){
        if(s->hasId(id)){
            if(auto e=newEntry.lock()){
                e->modify(newEntry);
                print("修改成功");
                return;
            }
        }
    }
    print("不存在此课程条目");
}
