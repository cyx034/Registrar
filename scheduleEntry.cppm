export module registrar:domain.scheduleEntry;
import std;
import :domain.schedule;
using std::weak_ptr;
using std::print;
using std::string;

export class ScheduleEntry
{
public:
    void modify(weak_ptr<ScheduleEntry> cheduleEntry);
    ScheduleEntry(string id,string sid,string classTime,string classRoom,weak_ptr<class Teacher> teacher,weak_ptr<class Course> course);
    ~ScheduleEntry();
    bool hasId(string id);
    void modify(string id);
private:
    string m_id;
    string m_sid;
    string m_classTime;
    string m_classRoom;
    weak_ptr<class Teacher> _teacher;
    weak_ptr<class Course> _course;
};

ScheduleEntry::ScheduleEntry(string id,string sid,string classTime,string classRoom,weak_ptr<Teacher> teacher,weak_ptr<Course> course)
    :m_id(id),m_sid(sid),m_classTime(classTime),m_classRoom(classRoom),_teacher(teacher),_course(course)
{}


ScheduleEntry::~ScheduleEntry()
{
    print("This ScheduleEntry isn't exit!!!");
}

bool ScheduleEntry::hasId(string id)
{
    return id==m_id;//判断是否有该条目id
}

//修改相关信息
void ScheduleEntry::modify(string id)
{

}



