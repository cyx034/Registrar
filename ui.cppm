export module registrar.ui;
import std;
import registrar;

using std::print;
using std::cin;
using std::vector;
using std::string;

export class Ui
{
public:
    Ui();
    void welcomeui();
    void studentui();
    void teacherui();
    void teachingsecretaryui();
private:
    Registrar& _registrar;
};

Ui::Ui()
    :_registrar(Registrar::system())
{
    _registrar.initialize();
}

void Ui::welcomeui()
{
    int choice=-1;
    while(choice != 4){
        print("\n-------------------------------------------\n");
        print("                  欢迎来到选课系统              \n\n");
        print("                  1.学生登录                   \n");
        print("                  2.教师登录                   \n");
        print("                  3.教务秘书登录                \n");
        print("                  4.退出系统                   \n\n");
        print("请选择登录身份: ");
        cin>>choice;
        switch(choice)
        {
            case 1:
                studentui();
                break;
            case 2:
                teacherui();
                break;
            case 3:
                teachingsecretaryui();
                break;
            case 4:
                print("感谢使用，再见！\n");
                break;
            default:
                print("输入无效，请重新选择!\n");
        }
    }
}

void Ui::studentui()
{
    string sid;
    print("请输入你的学号");
    cin>>sid;
    if(_registrar.affirmStudent(sid)){
        print("登录成功\n");
    }else{
        print("输入错误，登录失败！\n");
        return;
    }

    string cid;
    int choice=0;
    while(choice!=5){
        print("\n--------------------------------------------\n");
        print("                    学生系统                  \n\n");
        print("                  1.选课功能                   \n");
        print("                  2.退课功能                   \n");
        print("                  3.查看课表                   \n");
        print("                  4.查看成绩                   \n");
        print("                  5.返回主菜单                  \n\n");
        print("请选择你要进行的操作: ");
        cin>>choice;
        switch(choice)
        {
            case 1:
                //打印所有课程信息
                _registrar.printAllCourse();
                print("请输入要选择的课程号(输入-1停止）: ");
                cin>>cid;
                while(cid!="-1"){
                    _registrar.studentEnrollsInCourse(sid,cid);
                    print("请输入要选择的课程号(输入-1停止）: ");
                    cin>>cid;
                }
                break;
            case 2:
                print("请输入要退选的课程号(输入-1停止): ");
                cin>>cid;
                while(cid!="-1"){
                    _registrar.studentDropCourse(sid,cid);
                    print("请输入要退选的课程号(输入-1停止): ");
                    cin>>cid;
                }
                break;
            case 3:
                _registrar.classSchedule(sid);
                break;
            case 4:
                _registrar.printAllCourseGrade(sid);
                break;
            case 5:
                print("返回主菜单\n");
                break;
            default:
                print("输入无效，请重新选择!\n");
            }
    }
}

void Ui::teacherui()
{
    string tid;
    print("请输入你的教师号: ");
    cin>>tid;

    if(_registrar.affirmTeacher(tid)){
        print("登录成功\n");
    }else{
        print("输入错误，登录失败！\n");
        return;
    }

    int choice=0;
    while(choice!=3){
        print("\n--------------------------------------------\n");
        print("                     教师系统                  \n\n");
        print("                  1.录入成绩                   \n");
        print("                  2.查看授课课表                \n");
        print("                  3.返回主菜单                  \n\n");
        print("请选择你要进行的操作: ");
        cin>>choice;
        switch(choice)
        {
            case 1:
                _registrar.enterGradeManage(tid);
                break;
            case 2:
                //查看教师课表
                break;
            case 3:
                print("返回主菜单\n");
                break;
            default:
                print("输入无效，请重新选择!\n");
            }
    }
}

void Ui::teachingsecretaryui()
{
    string tsid;
    print("请输入你的教学秘书编号: ");
    cin>>tsid;

    if(_registrar.affirmSecretary(tsid)){
        print("登录成功\n");
    }else{
        print("输入错误，登录失败！\n");
        return;
    }

    string id,term,academy,major,gradelevel;
    string eid,time,room,tid,cid;
    string scheduleid,entryid;
    int choice=0;
    while(choice!=8){
        print("\n--------------------------------------------\n");
        print("                   教学秘书系统               \n\n");
        print("                  1.创建课程表                  \n");
        print("                  2.删除课程表                  \n");
        print("                  3.创建课程条目                \n");
        print("                  4.修改课程条目                \n");
        print("                  5.删除课程条目                \n");
        print("                  6.添加课程条目到课程表         \n");
        print("                  7.删除课程表中的课程条目        \n");
        print("                  8.返回主菜单                  \n\n");
        print("请选择你要进行的操作: ");
        cin>>choice;
        switch(choice){
            case 1:
                print("请输入课程表号: ");
                cin>>id;
                print("请输入当前学期: ");
                cin>>term;
                print("请输入所属学院: ");
                cin>>academy;
                print("请输入所属专业:");
                cin>>major;
                print("请输入年级: ");
                cin>>gradelevel;
                _registrar.createSchedules(tsid,id,term,academy,major,gradelevel);
                break;
            case 2:
                print("请输入你想删除的课程表号: ");
                cin>>id;
                _registrar.removeSchedules(tsid,id);
                break;
            case 3:

                print("请输入课程条目编号:");
                cin>>eid;
                print("请输入课程时间:");
                cin>>time;
                print("请输入所在教室:");
                cin>>room;
                print("请输入教师编号:");
                cin>>tid;
                print("请输入课程编号:");
                cin>>cid;
                _registrar.createScheduleEntrys(tsid,eid,time,room,tid,cid);
                break;
            case 4:
                choice=0;//初始化choice
                while(choice!=4){
                    print("请输入你要修改的课程条目编号: ");
                    cin>>id;
                    print("-------------课程条目:{}----------\n\n",id);
                    print("             1.修改时间           \n");
                    print("             2.修改地点           \n");
                    print("             3.修改授课老师        \n");
                    print("             4.返回上一页          \n");
                    print("请选择你要进行的操作: ");
                    cin>>choice;
                    switch(choice)
                    {
                        case 1:
                            print("请输入你要修改的时间：");
                            cin>>time;
                            _registrar.modifyEntrytime(id,time);
                            break;
                        case 2:
                            print("请输入你要修改的地点： ");
                            _registrar.modifyEntryroom(id,room);
                            break;
                        case 3:
                            print("请输入你要修改的教师编号：");
                            cin>>tid;
                            _registrar.modifyEntryteacher(id,tid);
                            break;
                        case 4:
                            print("返回上一页\n");
                            break;
                        default:
                            print("输入无效，请重新选择!\n");
                    }
                    break;
                case 5:
                    print("请输入你要删除的课程条目编号: ");
                    cin>>id;
                    _registrar.removeScheduleEntrys(tsid,id);
                    break;
                case 6:
                    print("请输入你要添加课程条目的课程表编号:");
                    cin>>scheduleid;
                    print("请输入你要添加到课程表的课程条目id:");
                    cin>>entryid;
                    _registrar.addEntrysToSchedule(tsid,scheduleid,entryid);
                    break;
                case 7:
                    print("请输入你要删除课程条目的课程表编号:");
                    cin>>scheduleid;
                    print("请输入你要删除到课程表的课程条目id:");
                    cin>>entryid;
                    _registrar.removeEntrysToSchedule(tsid,scheduleid,entryid);
                    break;
                case 8:
                    print("返回主菜单\n");
                    break;
                default:
                    print("输入无效，请重新选择!\n");
            }
        }
    }
}
