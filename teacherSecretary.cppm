export module registrar:domain.teacherSecretary;
import std;
import :domain.person;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::vector;
using std::print;

export class TeacherSecretary:public Person
{
public:
    TeacherSecretary(string id,string name,string academy);
    void createSchedule(string id);
    bool addEntryToSchedule(string id);
    bool removeEntryToSchedule(string id);
    void removeEntryToSchedule(string id,string entryId);
    bool modifySchedule(string id,string entryId);
private:
    vector<shared_ptr<class Schedule>> _schedules;
};

TeacherSecretary::TeacherSecretaryg(Person person)
    :Person(person)
{}

export class TeacherSecretary : public Person
{
public:
    TeacherSecretary(string id,string name,string academy);
    void createSchedule();
    void createScheduleEntry();
    void removeSchedule(shared_ptr<class Schedule> schedule)
    void removeScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry)；
    bool modifySchedule(string id);
    void modifyScheduleEntry(string sid);
    void addEntryToSchedule(shared_ptr<class Schedule> schedule,shared_ptr<class ScheduleEntry> scheduleEntry);
    void removeEntryToSchedule(shared_ptr<Schedule> schedule,shared_ptr<ScheduleEntry> scheduleEntry)

private:
    vector<shared_ptr<class Schedule>> _schedules;
    vector<shared_ptr<class ScheduleEntry>> _scheduleEntrys;
};

TeacherSecretary::TeacherSecretary(string id,string name,string academy)
    :Person(id,name,academy)
{}

//创建新的课程表
void TeacherSecretary::createSchedule()
{
    auto s=make_shared<Schedule>;
    _schedules.push_back(s);
    print("已成功创建一个新课程");
}

//创建新的课程条目
void TeacherSecretary::createScheduleEntry()
{
    auto e=make_shared<ScheduleEntry>;
    _scheduleEntrys.push_back(e);
}

//删除课程表
void TeacherSecretary::removeSchedule(shared_ptr<Schedule> schedule)
{
    _schedules.erase(schedule);
    print("成功删除该课程表");
}

//删除课程表条目
void TeacherSecretary::removeScheduleEntry(shared_ptr<ScheduleEntry> scheduleEntry)
{
    _scheduleEntrys.erase(s);
    print("成功删除该课程条目");
}

//向课程表中添加新的课程条目
void TeacherSecretary::addEntryToSchedule(shared_ptr<Schedule> schedule,shared_ptr<ScheduleEntry> scheduleEntry)
{
    schedule->addScheduleEntry(scheduleEntry);
}


//删除课程表的某个课程条目
void TeacherSecretary::removeEntryToSchedule(shared_ptr<Schedule> schedule,shared_ptr<ScheduleEntry> scheduleEntry)
{
    schedule->removeScheduleEntry(scheduleEntry);//课程表移除课程条目
}

//修改课程表信息
void TeacherSecretary::modifySchedule(string id)
{
    for(auto&s :_schedules){
        if(s->hasId(id)){
            s->modify(id);
            return;
        }
    }
    print("此课程不存在");
}

//修改课程条目的信息
bool TeacherSecretary::modifyScheduleEntry(string sid,string newId)
{
    for(auto&s :_scheduleEntrys){
        if(s->hasId(sid)){
            return s->modify(sid);
        }
    }
}

