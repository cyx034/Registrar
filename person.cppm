export module registrar:domain.person;
import std;

using std::string;

export class Person
{
public:
    Person(string id,string name,string academy);
    virtual ~Person();
    virtual string info();
    virtual bool hasId(string id);
private:
    string m_id;
    string m_name;
    string m_academy;
};

Person::Person(string id,string name,string academy)
    :m_id(id),m_name(name),m_academy(academy)
{}

Person::~Person()
{}

string Person::info()
{
    return format("{}  {}  {}\n", m_id, m_name,m_academy);
}

bool Person::hasId(string id)
{
    return id == m_id;
}
