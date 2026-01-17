export module registrar:domain.enrollment.grade;
import std;

using std::vector;

export class Grade
{
public:
    Grade(double midterm,double final,vector<double> homeworks);
    Grade(double grade);
    string info();

private:

    double score();
    double m_midterm;
    double m_final;
    vector<double> m_homeworks;
    double m_grade;
};

Grade::Grade(double midterm,double final,vector<double> homeworks)
    :m_midterm(midterm)
    ,m_final(final)
    ,m_homeworks(homeworks)
{
    grade = this->score();
}

Grade::Grade(double grade)
    :m_grade(grade)
{}

double Grade::score()
{
    //成绩已存在
    auto size = m_homeworks.size();
    if(size == 0) return 0;
    std::stable_sort(m_homeworks.begin(),m_homeworks.end());
    auto mid = size/2;
    double median;
    if(size % 2 == 0){
     median = (m_homeworks[mid] + m_homeworks[mid-1])/2;
    }else{
     median = m_homeworks[mid];
    }
    return 0.2 * m_midterm + 0.4 * m_final + 0.4 * median;
}

string Grade::info()
{
    return format("最终成绩为：{}  \n",m_grade);
}
