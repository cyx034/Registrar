//registrae.cppm
export module registrar;
export import :student;
export import :course;
export import :ui;

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

    void teacherEnterGrade(string sid,string cid,double midterm,double final,vector<double>homework);

    void courseRoster(string cid);  //打印指定课程的学生花名册（课程名单）
    void classSchedule(string sid);  //打印指定学生的课表
    void initialize();  //系统初始化

//教学秘书相关操作
    void Registrar::createSchedules(string id);
    void Registrar::createScheduleEntrys(string id);
    void Registrar::removeSchedules(string id，string sid);
    void Registrar::removeScheduleEntrys(string id, string sid);
    void Registrar::addEntrysToSchedule(string id,string sid,string eid);
    void Registrar::removeEntrysToSchedule(string id,string sid,string eid);
private:
    Registrar(); //禁止直接创建对象（将类的构造函数私有化，
                 //再配合静态成员函数来创建对象）
    StudentBroker _studentBroker;
    CourseBroker _courseBroker;
    TeacherBroker _teacherBroker;
    TeacherSecretaryBroker _secretaryBroker;
    EnrollmentBroker _enrollmenBroker;

};


//单例模式的静态局部变量实现。
Registrar& Registrar::system()
{
    static Registrar instance;  //局部静态变量
    return instance;
}

bool Registrar::teacherEnterGrade(string tid,string sid,string cid,double midterm,double final,vector<double>homework)
{
    if(tid.empty()||sid.empty()||cid.empty()||grade>100||grade<0){
        std::cerr << "数据错误" <<std::endl;
        return false;
    }
    auto teacher = _teacherBroker.findTeacherById(tid);
    auto student = _studentBroker.findStudentById(sid);
    auto course = _courseBroker.findCourseById(cid);

    if(teacher->CourseEvalueAccess(course)){
        auto enrollment = _enrollmenBroker.findEnrollmentById(sid,tid);

    }
}


//处理学生选课注册的逻辑
void Registrar::studentEnrollsInCourse(string sid,string cid)
{
    auto student = _studentBroker.findStudentById(sid);  //查找学生
    auto course = _courseBroker.findCourseById(cid);  //查找课程

    if(student && course){  //如果学生和课程都存在
        _enrollmenBroker.save();
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
    _enrollmenBroker.initialize();
}

Registrar::Registrar(){}


void Student::enrollIn(shared_ptr<class Course> course)
{
    if(!course) return;
    auto enrollment = course->acceptEnrollment(m_id);
    if(enrollment){
        _enrollments.push_back(enrollment); //复用Course返回的指针，不再重复创建
        print("选课成功\n");
    }else{
        print("选课失败\n");
    }
}

shared_ptr<Enrollment> Course::acceptEnrollment(string sid)
{
    //判断条件并添加选课记录
    //学分限制
    //课程冲突

    //避免重复选课
    auto it = std::find_if(_enrollments.begin(),_enrollments.end(),
                                [&sid,this](const shared_ptr<Enrollment>& en){
                                    return en->hasId(sid,m_id);
                                }
                            );
    if(it != _enrollments.end()) return nullptr;  //已存在，选课失败
    //创建共享的enrollment对象
    auto enrollment = make_shared<Enrollment>(sid,m_id);
    _enrollments.push_back(enrollment);
    return enrollment;   //返回这个智能指针给Student
}











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

//教学秘书创建新的课程表
void Registrar::createSchedules(string id)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    teacherSecretary->creatSchedule();
}

//教学秘书创建新的课程条目
void Registrar::createScheduleEntrys(string id)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    teacherSecretary->createScheduleEntrys();
}

//教学秘书删除课程表
void Registrar::removeSchedules(string id，string sid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    auto schedule = _schedulebroker.findScheduleById(sid);
    if(teacherSecretary&&schedule){
        teacherSecretary->removeSchedule(schedule);
    }
}

//教学秘书删除课程条目
void Registrar::removeScheduleEntrys(string id, string sid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    auto schedule = _schedulebroker.findScheduleById(sid);
    if(teacherSecretary&&schedule){
        teacherSecretary->removeScheduleEntry(schedule);
}

//教学秘书添加某课程条目到某课程表中
void Registrar::addEntrysToSchedule(string id,string sid,string eid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    auto schedule = _schedulebroker.findScheduleById(sid);
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(eid);
        if(teacherSecretary&&schedule&&scheduleEntry){
            teacherSecretary->addEntryToSchedule(schedule,scheduleEntry);
        }
    }
}

//教学秘书删除某课程表中的某课程条目
void Registrar::removeEntrysToSchedule(string id,string sid,string eid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    auto schedule = _schedulebroker.findScheduleById(sid);
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(eid);
        if(teacherSecretary&&schedule&&scheduleEntry){
            teacherSecretary->removeEntryToSchedule(schedule,scheduleEntry);
        }
    }
}
