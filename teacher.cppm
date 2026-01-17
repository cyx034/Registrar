export module registrar:domain.teacher;
import :domain.person;
import std;

using std::print;
using std::vector;
using std::shared_ptr;

export class Teacher : public Person
{
public:
    Teacher(Person person);
    virtual ~Teacher() override;
    void schedule();

    bool CourseEvalueAccess(shared_ptr<class Course> course);

private:
    vector<shared_ptr<class Course>> _courses;
};

Teacher::Teacher(Person person)
    :Person(person)
{}

Teacher::~Teacher()
{}

void Teacher::schedule()
{}

bool Teacher::CourseEvalueAccess(shared_ptr<Course> course)
{
    for(auto& c : _courses){
        if(c == course) return true;
    }
    return false;
}
