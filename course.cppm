export module registrar:domain.course;
import std;
import :domain.enrollment;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;

export class Course
{
public:
    Course(string id,string name);

    void acceptEnrollment(shared_ptr<Enrollment> enrollment);
    bool dropEnrollment(string sid);
    string info();
    bool hasId(string id);
private:
    string m_name;
    string m_id;
    short m_credit;

//    vector<share_ptr<string>> _enrollments;

    class Teacher _teacher;
    shared_ptr<class ScheduleEntry> _scheduleEntry;

};

Course::Course(string id, string name)
    : m_name(name)
    , m_id(id)
{}

/*void Course::acceptEnrollment(shared_ptr<Enrollment> enrollment)
{
    if(enrollment){
        _enrollments.push_back(enrollment);
    }
}



bool Course::dropEnrollment(string sid)
{
    auto it = std::find_if(_enrollments.begin(),_enrollments.end(),
                                [&sid,this](const shared_ptr<Enrollment>& en){
                                    return en->hasId(sid,m_id);
                                }
                            );
    if(it != _enrollments.end()){
        _enrollments.erase(it);
        return true;
    }
    return false;
}*/

string Course::info(){
    return format("{}   {}\n", m_id, m_name);
}

bool Course::hasId(string id){
    return id == m_id;
}
