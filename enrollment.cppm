export module enrollment;
import std;

using std::string;
using std::vector;
using std::shared_ptr;

export class Enrollment
{
public:
    Enrollment(string sid,string cid);
    ~Enrollment();
    bool hasId(string sid,string cid);

private:
    shared_ptr<string> _studentId;
    shared_ptr<string> _courseId;
    vector<unique_ptr<class Grade>> _grades;
};

Enrollment::Enrollment(string sid,string cid)
    :_studentId(sid)
    ,_courseId(cid)
{}

Enrollment::~Enrollment()
{}

bool Enrollemnt::hasId(string sid,string cid)
{
    return _studentId == sid && _courseId == cid;
}
