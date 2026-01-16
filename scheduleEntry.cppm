export module registrar:domain.scheduleEntry;
import std;
import :domain.schedule;
using std::weak_ptr;
using std::print;
using std::string;

export class ScheduleEntry
{
public:
    ScheduleEntry(string id,string classTime,string classRoom,int maxStudents,
                            int currentStudents,weak_ptr<Teacher> teacher,weak_ptr<Course> course)
    ~ScheduleEntry();
    void modify(weak_ptr<ScheduleEntry> cheduleEntry);

private:
    string m_id;
    string m_classTime;
    string m_classRoom;
    bool m_status;
//    int m_maxStudents;
//    int m_currentStudents;
    weak_ptr<Teacher> _teacher;
    weak_ptr<Course> _course;
};

ScheduleEntry::ScheduleEntry(string id,string classTime,string classRoom,int maxStudents,
                            int currentStudents,weak_ptr<teacher> teacher,weak_ptr<course> course)
    :m_id(id),m_classTime(clssTime),m_classRoom(classRoom),
     m_maxStudents(maxStudents),m_currentStudents(currentStudents)
     _teacher(teacher),_course(course)
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
void ScheduleEntry::modify(weak_ptr<ScheduleEntry> scheduleEntry)
{

}



