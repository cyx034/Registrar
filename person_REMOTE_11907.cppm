export module ?;
import std;

export class Person
{
public:
    Person(string id,string name,string academy);
    virtual ~Person;
    virtual string info();
    virtual bool hasId(string id);
private:
    string m_id;
    string m_name;
    string m_academy;
};

Person::Person()
    :m_id(id),
    m_name(name),
    m_academy(academy)
{}

Person::~Person()
{}

Person::string info()
{
    return format("id: {}, name: {}, academy: {}",m_id,m_name,m_academy);
}

Person::bool hasId(string id)
{
    return id == m_id;
}
