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

    double CourseEvalue();

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

double Teacher::CourseEvalue()
{
    double grade;

}
