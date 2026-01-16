export module ;
import std;
using std::vector;using std::weak_ptr;

//课程表
export class Schedule
{
public:
    Schedule(string id);
    ~Schedule();
    bool hasId(string id);
    void addScheduleEntry(string id);//添加课程条目
    void removeScheduleEntry(string id);//移除课程条目
    void modifyScheduleEntry(string id);//修改课程条目
private:
    string m_id;
    string m_name;
    string m_academy;
    double grade;
    vector<shared_ptr<ScheduleEntry>> _scheduleEntrys;
};

Schedule::Schedule(string id)
{
    print("The Schedule create");
}

Schedule::~Schedule()
{}

bool Schedule::hasId(string id)
{
    return id==m_id;//判断是否有该条目id
}

void Schedule::addScheduleEntry(string id)
{
   for(auto& s:_scheduleEntrys){
        if(s->hasId()){
            break;
        }
    }
    //--------//创建一个条目添加到容器中
    print("已成功添加该课程条目");
}

void Schedule::removeScheduleEntry(string id)
{
    for(auto& s:_scheduleEntrys){
        if(s->hasId()){
            _scheduleEntrys.erase(it);
            print("已成功删除该条目");
            break;
        }
    }
    print("不存在此课程条目");
}

void Schedule::modifyScheduleEntry(string id)
{
    for(auto& s:_scheduleEntrys){
        if(s->hasId()){
            s->modify();//---------输入相关修改信息
        }
    }
    print("不存在次课程条目");
}
