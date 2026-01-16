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
    TeacherSecretary(Person person);
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
    void createSchedule(string id);
    void createScheduleEntry();
    bool removeSchedule(string id);
    void removeScheduleEntry(string sId)；
    bool modifySchedule(string id);
    void modifyScheduleEntry(string sid);
    void addEntryToSchedule(string id，string sid);
    void removeEntryToSchedule(string id,string entryId);

private:
    vector<shared_ptr<class Schedule>> _schedules;
    vector<shared_ptr<class ScheduleEntry>> _scheduleEntrys;
};

TeacherSecretary::TeacherSecretary(string id,string name,string academy)
    :Person(id,name,academy)
{}

//创建新的课程表
void TeacherSecretary::createSchedule(string id)
{
    for(auto& s:_schedules){
        if(s->hasId(id)){
            print("此课程已存在");
            return;
        }
    }
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
void TeacherSecretary::removeSchedule(string id)
{
    for(auto&s :_schedules){
        if(s->hasId(id)){
            _schedules.erase(s);
            return;
        }
    }
    print("此课程不存在");
}

//删除课程表条目
void TeacherSecretary::removeScheduleEntry(string id)
{
    for(auto&s :_scheduleEntrys){
        if(s->hasId(id)){
            _scheduleEntrys.erase(s);//删除课程条目
            return;
        }
    }
    print("此课程条目不存在");
}

//向课程表中添加新的课程条目
void TeacherSecretary::addEntryToSchedule(string id，string sid)
{
    for(auto& s:_schedules){
        for(auto& se:_scheduleEntrys){
            if(s->hasId(id) && se->hasId(sid){
                s->addScheduleEntry(se);//课程表添加课程条目
                return;
        }
    }
    print("此课程不存在");
}


//删除课程表的某个课程条目
void TeacherSecretary::removeEntryToSchedule(string id,string entryId)
{
    for(auto&s :_schedules){
        for(auto& se:_scheduleEntrys){
            if(s->hasId(id)){
                s->removeScheduleEntry(se);//课程表移除课程条目
                return;
            }
        }
    }
    print("此课程不存在");
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
void TeacherSecretary::modifyScheduleEntry(string sid)
{

    for(auto&s :_scheduleEntrys){
        if(s->hasId(sid)){
            s->modify(sid);
            return;
        }
    }
    print("此课程条目不存在");
}

