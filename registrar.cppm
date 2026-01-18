//registrae.cppm
export module registrar;
export import :domain;
//export import :ui;

export import :broker;

import std;
using std::string;
using std::vector;
using std::make_unique;
using std::print;

export class Registrar
{
public:
    static Registrar& system();  //静态方法属于类，不属于对象
    void studentEnrollsInCourse(string sid,string cid); //处理学生选课注册的逻辑

    void studentDropCourse(string sid,string cid);

    bool teacherEnterGrade(string sid,string cid,double midterm,double final,vector<double>homework);

    void courseRoster(string cid);  //打印指定课程的学生花名册（课程名单）
    void classSchedule(string sid);  //打印指定学生的课表

    void printAllCourse();
    void enterGradeManage(string tid);

    void initialize();  //系统初始化

    //教学秘书相关操作
    void createSchedules(string tsid,string scheduleid,string term,string academy,string major,string gradelevel);//创建课程表
    void createScheduleEntrys(string tsid,string entryid,string classTime,string classRoom,string teacherid,string courseid);//创建课程条目
    void removeSchedules(string tsid,string scheduleid);
    void removeScheduleEntrys(string tsid, string entryid);//删除课程条目
    void addEntrysToSchedule(string tsid,string scheduleid,string entryid);//向课程表中添加课程条目
    void removeEntrysToSchedule(string tsid,string scheduleid,string entryid);//从课程表中移除课程条目

    //修改教学条目信息
    void modifyEntrytime(string entryid,string time);
    void modifyEntryroom(string entryid,string room);
    void modifyEntryteacher(string entryid,string teacherid);

    bool affirmStudent(string sid);
    bool affirmTeacher(string tid);
    bool affirmSecretary(string tsid);
private:
    Registrar(); //禁止直接创建对象（将类的构造函数私有化，
                 //再配合静态成员函数来创建对象）
    StudentBroker _studentBroker;
    CourseBroker _courseBroker;
    TeacherBroker _teacherBroker;
    TeacherSecretaryBroker _secretaryBroker;
    EnrollmentBroker _enrollmentBroker;
    ScheduleBroker _scheduleBroker;
    ScheduleEntryBroker _scheduleEntryBroker;

};

//单例模式的静态局部变量实现。
Registrar& Registrar::system()
{
    static Registrar instance;  //局部静态变量
    return instance;
}

bool Registrar::affirmStudent(string sid)
{
    if(_studentBroker.findStudentById(sid)){
        return true;
    }
    return false;
}

bool Registrar::affirmTeacher(string tid)
{
    if(_teacherBroker.findTeacherById(tid)){
        return true;
    }
    return false;
}

bool Registrar::affirmSecretary(string tsid)
{
    if(_secretaryBroker.findTeacherSecretaryById(tsid)){
        return true;
    }
    return false;
}


void Registrar::enterGradeManage(string tid)
{
    string cid,sid;
    double midterm,final;
    vector<double> homework;
    print("请输入课程号: ");
    std::cin>>cid;
    if(_courseBroker.CourseToTeacher(tid,cid)){
        print("请输入学生号: ");
        std::cin>>sid;
        if(_enrollmentBroker.findEnrollmentById(sid,cid)){
            print("请输入该学生的中期成绩和期末成绩: ");
            std::cin >> midterm >> final;
            print("请输入该学生家庭作业成绩: ");
            for(double h;std::cin>>h;){
                homework.push_back(h);
            }
            if(teacherEnterGrade(sid,cid,midterm,final,homework)){
                print("登入成绩成功！\n");
            }else{
                print("登入成绩失败！\n");
            }
        }else{
            print("该学生不在课程名单中！\n");
            return;
        }
    }else{
        //print("没有该课程权限！\n");
        return;
    }
}


void Registrar::printAllCourse()
{
    _courseBroker.courseEntry();
}


bool Registrar::teacherEnterGrade(string sid,string cid,double midterm,double final,vector<double>homework)
{
    if(sid.empty()||cid.empty()){
        std::cerr << "数据错误" <<std::endl;
        return false;
    }
    auto student = _studentBroker.findStudentById(sid);
    auto course = _courseBroker.findCourseById(cid);

    if(student && course){
        auto enrollment = _enrollmentBroker.findEnrollmentById(sid,cid);
        enrollment->computeSort(midterm,final,homework);//修改缓存成绩
        if(_enrollmentBroker.updateGrade(*enrollment)){
            return true;
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
       if(!_enrollmentBroker.save(sid,cid)){
           print("注册失败!\n");
        }
    }
}

//处理学生退课逻辑
void Registrar::studentDropCourse(string sid,string cid)
{
    auto student = _studentBroker.findStudentById(sid);  //查找学生
    auto course = _courseBroker.findCourseById(cid);  //查找课程

    if(student && course){  //如果学生和课程都存在
        if(!_enrollmentBroker.remove(sid,cid)){
            print("退课失败！\n");
        }
    }
}

//打印指定课程的学生花名册（课程名单）
/*void Registrar::courseRoster(string cid)
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
}*/


void Registrar::initialize()  //系统初始化
{
    _studentBroker.initialize();
    _courseBroker.initialize();
    _teacherBroker.initialize();
    _secretaryBroker.initialize();
    _enrollmentBroker.initialize();
    _scheduleBroker.initialize();
    _scheduleEntryBroker.initialize();
}

Registrar::Registrar(){}


//创建新的课程表
void Registrar::createSchedules(string tsid,string scheduleid,string term,string academy,string major,string gradelevel)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    if(!_scheduleBroker.save(scheduleid,term,academy,major,gradelevel)){
//    auto s=Schedule::create(scheduleid,term,academy,major,gradelevel);
//    teacherSecretary._schedules.push_back(s);
        print("创建失败！\n");
    }
}

//教学秘书创建新的课程条目
void Registrar::createScheduleEntrys(string tsid,string entryid,string classTime,string classRoom,string teacherid,string courseid)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    auto teacher = _teacherBroker.findTeacherById(teacherid);
    auto course = _courseBroker.findCourseById(courseid);
    if(!_scheduleEntryBroker.save(entryid,teacherid,courseid,classTime,classRoom)){
//    auto e=ScheduleEntry::createEntry(entryid,classTime,classRoom,teacher,course);
//    _scheduleEntrys.push_back(e);
        print("创建课程条目失败!\n");
    }
}

//删除课程表
void Registrar::removeSchedules(string tsid,string scheduleid)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    auto schedule = _scheduleBroker.findScheduleById(scheduleid);
    if(teacherSecretary&&schedule){
        if(!_scheduleBroker.remove(scheduleid)){
            //teacherSecretary->removeSchedule(schedule);
            print("删除课程表失败!\n");
        }
    }
}

//删除课程条目
void Registrar::removeScheduleEntrys(string tsid, string entryid)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    auto entry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    if(teacherSecretary&&entry){
        if(!_scheduleEntryBroker.remove(entryid)){
            //teacherSecretary->removeScheduleEntry(entry);
            print("删除课程条目失败!\n");
        }
    }
}

//添加某课程条目到某课程表中
void Registrar::addEntrysToSchedule(string tsid,string scheduleid,string entryid)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    auto schedule = _scheduleBroker.findScheduleById(scheduleid);
    auto scheduleEntry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    if(teacherSecretary&&schedule&&scheduleEntry){
        if(!_scheduleEntryBroker.addToSchedule(entryid,scheduleid)){
        //schedule->addScheduleEntry(scheduleEntry);
            print("添加课程条目到课程表失败！\n");
        }
    }
}

//删除某课程表中的某课程条目
void Registrar::removeEntrysToSchedule(string tsid,string scheduleid,string entryid)
{
    auto teacherSecretary = _secretaryBroker.findTeacherSecretaryById(tsid);
    auto schedule = _scheduleBroker.findScheduleById(scheduleid);
    auto scheduleEntry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    if(teacherSecretary&&schedule&&scheduleEntry){
        if(!_scheduleEntryBroker.removeToSchedule(entryid,scheduleid)){
            //schedule->removeScheduleEntry(scheduleEntry);
            print("删除课程表的课程条目失败\n");
        }
    }
}

void Registrar::modifyEntrytime(string entryid,string time)
{
    auto scheduleEntry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    if(scheduleEntry){
        if(!_scheduleEntryBroker.modifyEntrytime(entryid,time)){
            //scheduleEntry->modifyTime(time);
            print("修改时间失败\n");
        }
    }
}

void Registrar::modifyEntryroom(string entryid,string room)
{
    auto scheduleEntry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    if(scheduleEntry){
        if(!_scheduleEntryBroker.modifyEntryroom(entryid,room)){
            //scheduleEntry->modifyRoom(room);
            print("修改教师失败\n");
        }
    }
}

//修改课程条目的任课老师
void Registrar::modifyEntryteacher(string entryid,string teacherid)
{
    auto scheduleEntry = _scheduleEntryBroker.findScheduleEntryById(entryid);
    auto teacher = _teacherBroker.findTeacherById(teacherid);
    if(scheduleEntry){
        if(!_scheduleEntryBroker.modifyEntryteacher(entryid,teacherid)){
            //scheduleEntry->modifyTeacher(teacher);
            print("修改老师失败\n");
        }
    }
}


