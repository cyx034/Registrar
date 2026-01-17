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
    void createSchedules(string tsid,string scheduleid,string term,string academy,string major,string gradelevel);//创建课程表
    void createScheduleEntrys(string tsid);//创建课程条目
    void removeSchedules(string tsid，string scheduleid);//删除课程表
    void removeScheduleEntrys(string tsid, string entryid);//删除课程条目
    void addEntrysToSchedule(string tsid,string scheduleid,string entryid);//向课程表中添加课程条目
    void removeEntrysToSchedule(string tsid,string scheduleid,string entryid);//从课程表中移除课程条目

    //修改教学条目信息
    void modifyEntrytime(string entryid,string time);
    void modifyEntryroom(string entryid,string room);
    void modifyEntryteacher(string entryid,string teacherid);
    void modifyEntrycourse(string entryd,string courseid);
private:
    Registrar(); //禁止直接创建对象（将类的构造函数私有化，
                 //再配合静态成员函数来创建对象）
    StudentBroker _studentBroker;
    CourseBroker _courseBroker;
    TeacherBroker _teacherBroker;
    TeacherSecretaryBroker _secretaryBroker;
    EnrollmentBroker _enrollmentBroker;

};


//单例模式的静态局部变量实现。
Registrar& Registrar::system()
{
    static Registrar instance;  //局部静态变量
    return instance;
}

bool Registrar::teacherEnterGrade(string tid,string sid,string cid,double midterm,double final,vector<double>homework)
{
    if(tid.empty()||sid.empty()||cid.empty()){
        std::cerr << "数据错误" <<std::endl;
        return false;
    }
    auto teacher = _teacherBroker.findTeacherById(tid);
    auto student = _studentBroker.findStudentById(sid);
    auto course = _courseBroker.findCourseById(cid);

    if(student && course && teacher){
        if(_courseBroker.CourseEvalueAccess(cid,tid)){
            auto enrollment = _enrollmentBroker.findEnrollmentById(sid,cid);
            enrollment.computeSort(midterm,final,homework);//修改缓存成绩
            if(_enrollmentBroker.updateGrade(enrollment)){
                return true;
            }
        }else{
            print("没有权限\n");
            return false;
        }
    }
    return false;
}


//处理学生选课注册的逻辑
void Registrar::studentEnrollsInCourse(string sid,string cid)
{
    auto student = _studentBroker.findStudentById(sid);  //查找学生
    auto course = _courseBroker.findCourseById(cid);  //查找课程

    if(student && course){  //如果学生和课程都存在
        if(auto enrollment = _enrollmenBroker.save(sid,cid)){
            student -> enrollIn(enrollment);  //执行注册
            course -> acceptEnrollment(enrollment);
        }
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
    _enrollmentBroker.initialize();
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

//教学秘书创建新的课程表
void Registrar::createSchedules(string tsid,string scheduleid,string term,string academy,string major,string gradelevel)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(tsid);
    teacherSecretary->creatSchedule(scheduleid,term,academy,major,gradelevel);
}

//教学秘书创建新的课程条目
void Registrar::createScheduleEntrys(string tsid,string entryid,string classTime,string classRoom,string teacherid,string courseid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(tsid);
    auto teacher = _teacherBroker.findTeacherById(teacherid);
    auto course = _courseBroker.findCourseById(courseid);
    teacherSecretary->createScheduleEntrys(entryid,classTime,classRoom,teacher,course);
}

//教学秘书删除课程表
void Registrar::removeSchedules(string tsid，string scheduleid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(id);
    auto schedule = _schedulebroker.findScheduleById(sid);
    if(teacherSecretary&&schedule){
        teacherSecretary->removeSchedule(schedule);
    }
}

//教学秘书删除课程条目
void Registrar::removeScheduleEntrys(string tsid, string scheduleid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(tsid);
    auto schedule = _schedulebroker.findScheduleById(scheduleid);
    if(teacherSecretary&&schedule){
        teacherSecretary->removeScheduleEntry(schedule);
    }
}

//教学秘书添加某课程条目到某课程表中
void Registrar::addEntrysToSchedule(string tsid,string scheduleid,string entryid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(tsid);
    auto schedule = _schedulebroker.findScheduleById(scheduleid);
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    if(teacherSecretary&&schedule&&scheduleEntry){
        teacherSecretary->addEntryToSchedule(schedule,scheduleEntry);
    }
}

//教学秘书删除某课程表中的某课程条目
void Registrar::removeEntrysToSchedule(string tsid,string scheduleid,string entryid)
{
    auto teacherSecretary = _teachersecretarybroker.findTeacherSecretaryById(tsid);
    auto schedule = _schedulebroker.findScheduleById(scheduleid);
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    if(teacherSecretary&&schedule&&scheduleEntry){
        teacherSecretary->removeEntryToSchedule(schedule,scheduleEntry);
    }
}

void Registrar::modifyEntrytime(string entryid,string time)
{
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    if(scheduleEntry){
        scheduleEntry->modifyTime(time);
    }
}

void Registrar::modifyEntryroom(string entryid,string room)
{
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    if(scheduleEntry){
        scheduleEntry->modifyRoom(room);
    }
}

//修改课程条目的任课老师
void Registrar::modifyEntryteacher(string entryid,string teacherid)
{
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    auto teacher = _teacherBroker.findTeacherById(teacherid);
    scheduleEntry->modifyTeacher(teacher);
}

//修改课程条目的课程
void Registrar::modifyEntrycourse(entryid,courseid)
{
    auto scheduleEntry = _scheduleEntrybroker.findScheduleEntryById(entryid);
    auto course = _courseBroker.findTeacherById(courseid);
    scheduleEntry->modifyCourse(course);
}

