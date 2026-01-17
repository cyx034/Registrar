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
    shared_ptr<ScheduleEntry> createEntry(string entryid,string classTime,string classRoom,weak_ptr<Teacher> teacher,weak_ptr<Course>course);
    void modifyRoom(string room);
    void modifyTime(string time);
    void modifyTeacher(weak_ptr<class Teacher> teacher);
    void modifyCourse(weak_ptr<class Course> Course);
private:
    string m_id;
    string m_sid;
    string m_classTime;
    string m_classRoom;
    weak_ptr<class Teacher> _teacher;
    weak_ptr<class Course> _course;
};

ScheduleEntry::ScheduleEntry(string id,string classTime,string classRoom,weak_ptr<Teacher> teacher,weak_ptr<Course> course)
    :m_id(id),m_classTime(classTime),m_classRoom(classRoom),_teacher(teacher),_course(course)
{}


ScheduleEntry::~ScheduleEntry()
{
    print("This ScheduleEntry isn't exit!!!");
}

shared_ptr<ScheduleEntry> ScheduleEntry::createEntry(string entryid,string classTime,string classRoom,weak_ptr<Teacher> teacher,weak_ptr<Course>course)
{
    return make_shared<ScheduleEntry>(entryid,classTime,classRoom,teacher,course);
}

void ScheduleEntry::modifyTime(string time)
{
    m_classTime = time;
}

void ScheduleEntry::modifyRoom(string room)
{
    m_classRoom = room;
}

//修改老师
void ScheduleEntry::modifyTeacher(weak_ptr<Teacher> teacher)
{
    if(auto t=teacher.lock()){
        _teacher=teacher;
    }else{
        print("无效，无法修改");
    }
}

//修改课程
void ScheduleEntry::modifyCourse(weak_ptr<Course> course)
{
    if(auto c=course.lock()){
        _course=course;
    }else{
        print("无效，无法修改");
    }
}




