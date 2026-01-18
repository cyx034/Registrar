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
    Student(string id,string name,string academy,string major); //初始化

    void enrollIn(shared_ptr<Enrollment> enrollment);
    void dropIn(shared_ptr<class Course> course);
    void schedule();
    void transcript();

private:
    string m_major;
    string m_gradelevel;
//    vector<shared_ptr<string>> _enrollments;
};

Student::Student(string id,string name,string academy,string major)
    :Person(id,name,academy)
    ,m_major(major)
{}

/*void Student::enrollIn(shared_ptr<Enrollment> enrollment)
{
    if(enrollment){
        _enrollments.push_back(enrollment);
     }
}


void Student::dropIn(shared_ptr<class Course> course)
{


}*/

void Student::schedule()
{

}

void Student::transcript()
{

}
