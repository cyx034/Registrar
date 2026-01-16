export module registrar:domain.teacher;
import :domain.person;
import std;

using std::print;

export class Teacher : public Person
{
public:
    Teacher(Person person);
    virtual ~Teacher() override;
    void schedule();
private:
    vector<shared_ptr<class Course> _courses;
};

Teacher::Teacher(Person person)
    :Person(person)
{}

Teacher::~Teacher()
{}

void Teacher::schedule()
{

}
