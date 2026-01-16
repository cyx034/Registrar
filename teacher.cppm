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
};

Teacher::Teacher(Person person)
    :Person(person)
{}

Teacher::~Teacher()
{}

Teacher::void schedule()
{}
