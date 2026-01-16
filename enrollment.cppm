export module registrar:domain.enrollment;
import std;

using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

export class Enrollment
{
public:
    Enrollment(string sid,string cid);
    ~Enrollment();
    bool hasId(string sid,string cid);

private:
    string _sid;
    string _cid;
    vector<unique_ptr<class Grade>> _grades;
};

Enrollment::Enrollment(string sid,string cid)
    :_sid(sid)
    ,_cid(cid)
{}

Enrollment::~Enrollment()
{}

bool Enrollment::hasId(string sid,string cid)
{
    return _sid == sid && _cid == cid;
}
