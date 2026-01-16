export module   ;
import //导入基类
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
