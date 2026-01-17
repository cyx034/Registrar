export module registrar:domain.scheduleEntry;
import std;
import :domain.schedule;
using std::weak_ptr;
using std::print;
using std::string;

export class ScheduleEntry
{
public:
    ScheduleEntry(string id,string classTime,string classRoom,weak_ptr<class Teacher> teacher,weak_ptr<class Course> course);
    ~ScheduleEntry();
    void modifyTeacher(shared_ptr<class Teacher> teacher);
    void modifyCourse(shared_ptr<class Course> Course);
    void modifyTime(string time);
    void modifyRoom(string room);
private:
    string m_id;
    string m_sid;
    string m_classTime;
    string m_classRoom;
    shared_ptr<class Teacher> _teacher;
    shared_ptr<class Course> _course;
};

ScheduleEntry::ScheduleEntry(string id,string classTime,string classRoom,weak_ptr<Teacher> teacher,weak_ptr<Course> course)
    :m_id(id),m_classTime(classTime),m_classRoom(classRoom),_teacher(teacher),_course(course)
{}


ScheduleEntry::~ScheduleEntry()
{
    print("This ScheduleEntry isn't exit!!!");
}

//修改老师
void ScheduleEntry::modifyTeacher(shared_ptr<Teacher> teacher)
{
    _teacher=teacher;
}

void ScheduleEntry::modifyTime(string time)
{
    m_classTime = time;
}

void ScheduleEntry::modifyRoom(string room)
{
    m_classRoom = room;
}





