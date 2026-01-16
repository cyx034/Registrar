export module ?;
import std;
using std::shared_ptr;

export class TeacherSecretaryg:public Person
{
public:
    TeacherSecretaryg(Person person);
    void createSchedule(string id);
    bool addEntryToSchedule(string id);
    bool removeEntryToSchedule(string id);
    void removeEntryToSchedule(string id,string entryId)；
    bool modifySchedule(string id,string entryId);
private:
    vector<shared_ptr<Schedule>> _schedules;
};

TeacherSecretaryg::TeacherSecretaryg(Person person)
    :Person(person)
{}


//创建新的课程表
void TeacherSecretaryg::createSchedule(string id)
{
    for(auto& s:_schedules){
        if(hasId(id)){
            print("此课程已存在");
            return;
        }
    }
    auto s=make_shared<Schedule>;
    _schedules.push_back(s);
    print("已成功创建一个新课程");
}

//删除课程表
void TeacherSecretaryg::removeSchedule(string id)
{
    for(auto&s :_schedules){
        if(s->hasId(id)){
            _schedules.erase(s);//课程表移除课程条目
            return;
        }
    }
    print("此课程不存在");
}

//向课程表中添加新的课程条目
void TeacherSecretaryg::addEntryToSchedule(string id)
{
    for(auto& s:_schedules){
        if(s->hasId(id)){
            s->addScheduleEntry();//课程表添加课程条目
            return;
        }
    }
    print("此课程不存在");
}


//删除课程表的某个课程条目
void TeacherSecretaryg::removeEntryToSchedule(string id,string entryId)
{
    for(auto&s :_schedules){
        if(s->hasId(id)){
            s->removeScheduleEntry(Id);//课程表移除课程条目
            return;
        }
    }
    print("此课程不存在");
}

//修改课程表中的某个课程条目
void TeacherSecretaryg::modifySchedule(string id,string entryId)
{
    for(auto&s :_schedules){
        if(s->hasId(id)){
            schedule->modifyScheduleEntry(Id);//课程表修改课程条目
        }
    }
}
