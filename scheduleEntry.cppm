export module ;
import std;
using std::weak_ptr;

export class ScheduleEntry
{
public:
    ScheduleEntry(weak_ptr<class Teacher> teacher, weak_ptr<class Course> course);
    ~ScheduleEntry();
    void modify();
    //int setStatus(int newStatus);
private:
    string m_id;
    string m_classTime;
    string m_classRoom;
    bool m_status;
    int m_maxStudents;
    int m_currentStudents;
    weak_ptr<Teacher> _teacher;
    weak_ptr<Course> _course
};

ScheduleEntry::ScheduleEntry()
    :m_id(id),m_classTime(
    string m_classRoom;
    bool m_status;
    int m_maxStudents;
    int m_currentStudents;
    weak_ptr<Teacher> _teacher;
    weak_ptr<Course> _course;
{}


ScheduleEntry::~ScheduleEntry()
{
    print("This ScheduleEntry isn't exit!!!");
}

string ScheduleEntry::setId(string id)
{
    m_id=id;//设置条目id
}

bool ScheduleEntry::hasId(string id)
{
    return id==m_id;//判断是否有该条目id
}

void ScheduleEntry::modify()
{
    //-----------------//修改相关信息
}



