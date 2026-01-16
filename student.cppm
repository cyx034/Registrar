export module person:student;
import std;
import person;

using std::string;
using std::shared_ptr;

export class Student : public Person
{
public:
    Student(string id,string name,string major,string gradelevel);  //初始化
    ~Student();

    void enrollIn(string cid);
    void dropIn(string cid);
    void schedule();
    void transcript();

private:
    string m_major;
    string m_gradelevel;
    vector<shared_ptr<class Enrollment>> _enrollments;
};

Student::Student(string id, string name,string major,string gradelevel)
    :Person(id,name)
    ,m_major(major)
    ,m_gradelevel(gradelevel)
{}

Student::~Student()
{}

void Student::enrollIn(string cid)
{
    //通过id查找课程
    if(course->acceptEnrollment(m_id)){
        _enrollments.push_back(make_shared<Enrollment>(m_id,cid));
        print("选课成功\n");
    }
}

void Student::dropIn(string cid)
{
    //通过id找到课程
    if(!course->dropenrollment(m_id)){
        print("退课失败，你未选该课程!\n");
        return;
    }
    auto it = std::remove_if(_enrollments.begin(),_enrollments.end(),
                                [&](const shared_ptr<Enrollment>& en)){
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
