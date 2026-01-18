export module registrar:domain.teacherSecretary;
import std;
import :domain.person;

using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;
using std::string;
using std::vector;
using std::print;

export class TeacherSecretary : public Person
{
public:
    TeacherSecretary(string id,string name,string academy);
    void removeSchedule(shared_ptr<class Schedule> schedule);
    void removeScheduleEntry(shared_ptr<class ScheduleEntry> scheduleEntry);

private:
    vector<shared_ptr<class Schedule>> _schedules;
    vector<shared_ptr<class ScheduleEntry>> _scheduleEntrys;
};

TeacherSecretary::TeacherSecretary(string id,string name,string academy)
    :Person(id,name,academy)
{}


//删除课程表
void TeacherSecretary::removeSchedule(shared_ptr<Schedule> schedule)
{
    auto it = std::find(_schedules.begin(),_schedules.end(),schedule);
    if(it!=_schedules.end()){
        _schedules.erase(it);
        print("成功删除该课程表");
    }else{
        print("无该课程表");
    }
}

//删除课程表条目
void TeacherSecretary::removeScheduleEntry(shared_ptr<ScheduleEntry> scheduleEntry)
{
    auto it = std::find(_scheduleEntrys.begin(),_scheduleEntrys.end(),scheduleEntry);
    if(it!=_scheduleEntrys.end()){
        _scheduleEntrys.erase(it);
        print("成功删除该课程条目");
    }else{
        print("无该课程条目");
    }
}

