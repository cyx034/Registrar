export module course;
import std;

using std::string;
using std::shared_ptr;
using std::make_shared;

export class Course
{
public:
    Course(string id,string name);
    ~Course();

    bool acceptEnrollment(string sid);
    bool dropEnrollment(string sid);
    string info();
    bool hasId(string id);
private:
    string m_name;
    string m_id;
    short m_credit;

    vector<shared_ptr<class Enrollment>> _enrollments;
    vector<shared_ptr<class Teacher>> _teachers;
    shared_ptr<class ScheduleEntry> _scheduleEntry;

};

Course::Course(string id, string name)
    : m_name(name)
    , m_id(id)
{}

Course::~Course()
{}

bool Course::acceptEnrollment(string sid)
{
    //判断条件并添加选课记录
    if(_enrollments.size() > 60){   //人数限制
        return false;
    }
    //学分限制
    //课程冲突

    //避免重复选课
    auto it = std::find_if(_enrollments.begin(),_enrollments.end(),
                                [&sid](const shared_ptr<Enrollment>& en){
                                    return en->hasId(sid,m_id);
                                }
                            );
    if(it != _enrollments.end()) return false;  //已存在，选课失败

    _enrollments.push_back(make_shared<Enrollment>(sid,m_id));

    return true;
}

bool Course::dropEnrollment(string sid)
{
    auto it = std::find_if(_enrollments.begin(),_enrollments.end(),
                                [&sid](const shared_ptr<Enrollment>& en){
                                    return en->hasId(sid,m_id);
                                }
                            );
    if(it != _enrollments.end()){
        _enrollments.erase(it);
        return true;
    }
    return false;
}

string Course::info(){
    return format("{}   {}\n", m_id, m_name);
}

bool Course::hasId(string id){
    return id == m_id;
}
