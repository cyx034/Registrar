//registrae.cppm
export module registrar;
export import :student;
export import :course;


export import :broker;

import std;
using std::string;
using std::vector;
using std::make_unique;

export class Registrar
{
public:
    static Registrar& system();  //静态方法属于类，不属于对象
    void studentEnrollsInCourse(string sid,string cid); //处理学生选课注册的逻辑

    void studentDropCourse(string sid,string cid);

    void courseRoster(string cid);  //打印指定课程的学生花名册（课程名单）
    void classSchedule(string sid);  //打印指定学生的课表
    void initialize();  //系统初始化

private:
    Registrar(); //禁止直接创建对象（将类的构造函数私有化，
                 //再配合静态成员函数来创建对象）
    StudentBroker _studentBroker;
    CourseBroker _courseBroker;
    Teacher _teacherBroker;
    TeacherSecretary _secretaryBroker;
};


//单例模式的静态局部变量实现。
Registrar& Registrar::system()
{
    static Registrar instance;  //局部静态变量
    return instance;
}

//处理学生选课注册的逻辑
void Registrar::studentEnrollsInCourse(string sid,string cid)
{
    auto student = _studentBroker.findStudentById(sid);  //查找学生
    auto course = _courseBroker.findCourseById(cid);  //查找课程

    if(student && course){  //如果学生和课程都存在
        student -> enrollIn(course);  //执行注册
    }
}

//处理学生退课逻辑
void Registrar::studentDropCourse(string sid,string cid)
{
    auto student = _studentBroker.findStudentById(sid);  //查找学生
    auto course = _courseBroker.findCourseById(cid);  //查找课程

    if(student && course){  //如果学生和课程都存在
       student -> dropOut(course);  //执行注册
    }
}

//打印指定课程的学生花名册（课程名单）
void Registrar::courseRoster(string cid)
{
    auto c = _courseBroker.findCourseById(cid); //查找课程
    //缺少空指针检查
    print("{}\n",c->roster());
}

//打印指定学生的课表
void Registrar::classSchedule(string sid)
{
    auto s = _studentBroker.findStudentById(sid);
    print("{}\n",s->printSchedules());
}


void Registrar::initialize()  //系统初始化
{
    _studentBroker.initialize();
    _courseBroker.initialize();
    _teacherBroker.initialize();
    _secretaryBroker.initialize();
}

Registrar::Registrar(){}


//根据student的运行时类型调用enrollIn
//根据course的运行时类型调用acceptEnrollment,要么双方都更新，要么都不更新

void Student::enrollIn(Course *course)
{
    if(course->acceptEnrollment(this))  //this 是指向当前Student对象的指针
        _courses.push_back(course);
}

//输出每个课程所有选课的学生名单
void Student::dropOut(class Course* course)
{
    if(course->acceptDropOut(this))  //this 是指向当前Student对象的指针
        for(int i=0;i<_courses.size();i++){
            if(_courses[i] == course){
                _courses.erase(_courses.begin()+i);
                break;
            }
        }
}

//输出该课程所有选课的学生名单
string Course::roster()
{
    auto rst = format("{} selected by the students:\n",m_name);
    for(auto s : _students){
        rst += s->info();
    }
    return rst;
}

//输出该学生的课表
string Student::printSchedules()
{
    auto rst = format("{} schedule:\n",m_name);
    for(auto c : _courses){
        rst += c->info();
    }
    return rst;
}

//=delete =default const constexpr explicit
//

