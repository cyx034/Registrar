export module registrar:domain.student;
import std;
import :domain.person;
import :domain.enrollment;

using std::string;
using std::shared_ptr;
using std::vector;
using std::print;

export class Student : public Person
{
public:
    Student(string id,string name,string major,string gradelevel); //初始化
    ~Student();

    void enrollIn(shared_ptr<class Course> course);
    void dropIn(shared_ptr<class Course> course);
    void schedule();
    void transcript();

private:
    string m_major;
    string m_gradelevel;
    vector<shared_ptr<class Enrollment>> _enrollments;
};

Student::Student(string id,string name,string major,string gradelevel)
    :Person(id,name)
    ,m_major(major)
    ,m_gradelevel(gradelevel)
{}

Student::~Student()
{}


void Student::dropIn(shared_ptr<class Course> course)
{
    if(!course) return;
    string info = course->info();
    //获得cid
    string cid = info.substr(0,info.find(' '));
    if(!course->dropEnrollment(m_id)){
        print("退课失败，你未选该课程!\n");
        return;
    }
    //移除学生的enrollment
    auto it = std::remove_if(_enrollments.begin(),_enrollments.end(),
                                [this,&cid](const shared_ptr<Enrollment>& en){
                                    return en->hasId(m_id,cid);
                                }
                            );
    if(it != _enrollments.end()){
        _enrollments.erase(it,_enrollments.end());
        print("退课成功\n");
    }
}

void Student::schedule()
{

}

void Student::transcript()
{

}
