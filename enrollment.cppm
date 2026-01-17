export module registrar:domain.enrollment;
import std;
import :domain.enrollment.grade;

using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;

export class Enrollment
{
    friend class EnrollmentBroker;
public:
    Enrollment(string sid,string cid,double grade);
    bool hasId(string sid,string cid);

private:
    string _sid;
    string _cid;
    Grade _grade;
};

//从数据库中读取最终成绩
Enrollment::Enrollment(string sid,string cid,double grade)
    :_sid(sid)
    ,_cid(cid)
    ,_grade(grade)
{}

bool Enrollment::hasId(string sid,string cid)
{
    return _sid == sid && _cid == cid;
}

void Enrollment::computeSort(double midterm,double final,vector<double> homework)
{
    _grade.reset(double midterm,double final,vector<double> homework);  //教师输入成绩，重新修改最终成绩
}
