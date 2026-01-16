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
    double CourseEvalue(shared_ptr<Course> course);

private:
    vector<shared_ptr<class Course>> _courses;
};

Teacher::Teacher(Person person)
    :Person(person)
{}

Teacher::~Teacher()
{}


Teacher::void schedule()
{}

double Teacher::CourseEvalue(shared_ptr<Course> course)
{
    double grade;
    print("You want to ")
}
