export module registrar:domain.course;
import std;
import :domain.enrollment;
import :domain.teacher;
import :domain.scheduleEntry;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::vector;

export class Course
{
public:
    Course(string id, string name,string credit,string academy,string tracherId);

//    void acceptEnrollment(shared_ptr<Enrollment> enrollment);
//    bool dropEnrollment(string sid);
    string info();
    bool hasId(string id);
private:
    string m_id;
    string m_name;
    string m_credit;
    string m_academy;

//    vector<shared_ptr<string>> _enrollments;
    string _teacherId;
    shared_ptr<ScheduleEntry> _scheduleEntry;

};

Course::Course(string id, string name,string credit,string academy,string teacherId)
    : m_id(id),m_name(name),m_credit(credit),m_academy(academy),_teacherId(teacherId)
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
