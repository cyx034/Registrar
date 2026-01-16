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
<<<<<<< Updated upstream
    double CourseEvalue(shared_ptr<class Course> course);
=======
    double CourseEvalue(shared_ptr<Course> course);
>>>>>>> Stashed changes

private:
    vector<shared_ptr<class Course>> _courses;
};

Teacher::Teacher(Person person)
    :Person(person)
{}

Teacher::~Teacher()
{}


<<<<<<< Updated upstream
void Teacher::schedule()
=======
Teacher::void schedule()
>>>>>>> Stashed changes
{}

double Teacher::CourseEvalue(shared_ptr<Course> course)
{
    double grade;
<<<<<<< Updated upstream
=======
    print("You want to ")
>>>>>>> Stashed changes
}
