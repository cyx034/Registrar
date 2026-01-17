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
    bool hasId(string sid,string cid);

private:
    string _sid;
    string _cid;
    Grade _grade;
};

Enrollment::Enrollment(string sid,string cid,double midterm,double final,vector<double> homework)
    :_sid(sid)
    ,_cid(cid)
    ,_grade(midterm,final,homework)
{}

Enrollment::Enrollment(string sid,string cid,double grade)
    :_sid(sid)
    ,_cid(cid)
    ,_grade(grade)
{}


bool Enrollment::hasId(string sid,string cid)
{
    return _sid == sid && _cid == cid;
}
