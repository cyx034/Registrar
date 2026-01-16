export module ?;
import std;
using std::shared_ptr;

export class TeacherSecretaryg:public Person
{
public:
    TeacherSecretaryg(Person person);
    virtual ~TeacherSecretaryg() override;
    Schedule createSchedule();
    bool addEntryToSchedule();
    bool removeEntryToSchedule();
    bool modifySchedule();
private:
    vector<shared_ptr<Schedule>> _schedules;
};

TeacherSecretaryg::TeacherSecretaryg(Person person)
    :Person(person)
{}

TeacherSecretaryg::~TeacherSecretaryg()
{}

shared_ptr<Schedule> TeacherSecretaryg::createSchedule()
{}

Schedule TeacherSecretaryg::createSchedule()
{
    auto s=make_shared<Schedule>;
    _schedules.push_back(s);
    print("已成功创建一个新课程");
}

void TeacherSecretaryg::addEntryToSchedule(string id)
{
    for(auto& s:_schedules){
        if(s->hasId()){
            break;
        }
    }
    schedule->addScheduleEntry(id);//课程表添加课程条目
}


void TeacherSecretaryg::removeEntryToSchedule(string id)
{
    for(auto&s :_schedules){
        if(s->hasId){
            schedule->removeScheduleEntry();//课程表移除课程条目
        }
    }
}

void TeacherSecretaryg::modifySchedule()
{
    for(auto&s :_schedules){
        if(s->hasId){
            schedule->modifyScheduleEntry();//课程表修改课程条目
        }
    }
}
