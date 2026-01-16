export module registrar:domain.person;
import std;

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

Person::string info()
{
<<<<<<< HEAD
    return format("{}  {}  {}\n", m_id, m_name,m_academy);
=======
    return format("{}   {}    {}",m_id,m_name,m_academy);
>>>>>>> 49c0097 (领域层，进一步实现排课，对原来的初步版本进行了修改，进一步调整了关于课程表和课程条目的操作)
}

bool Person::hasId(string id)
{
    return id == m_id;
}
