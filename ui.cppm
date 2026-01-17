export module registrar:ui;
import std;
import registrar;

using std::print;
using std::cin;
using std::vector;

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
    _registrar.initialize()
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
    print("登录成功\n");   //未添加判断

    int choice;
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
            string cid;
            print("请输入要选择的课程号: ");
            cin>>cid;
            _registrar.studentEnrollsInCourse(sid,cid);
            break;
        case 2:
            string cid1;
            print("请输入要退选的课程号: ");
            cin>>cid1;
            _registrar.studentDropCourse(sid,cid1);
            break;
        case 3:
            _registrar.classSchedule(sid);
            break;
        case 4:
            break;
        case 5:
            print("返回主菜单\n");
            break;
        default:
            print("输入无效，请重新选择!\n");
    }
}

void Ui::teacherui()
{
    string tid;
    print("请输入你的教师号: ");
    cin>>tid;
    print("登录成功\n");   //未添加判断

    int choice;
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
            string cid;
            string sid;
            double grade;
            print("请输入课程号: ");
            cin>>cid;
            print("请输入学生号: ");
            cin>>sid;
            print("请输入该学生的中期成绩和期末成绩: ");
            double midterm ,final;
            cin >> midterm >> final;
            print("请输入该学生家庭作业成绩: ");
            vector<double> homework;
            for(double h;cin>>h){
                homework.push_back(h);
            }
            _registrar.teacherEnterGrade(tid,sid,cid,midterm,final,homework);
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

void Ui::teachingsecretaryui()
{
    string tsid;
    print("请输入你的教学秘书编号: ");
    cin>>tsid;
    print("登录成功\n");   //未添加判断

    int choice;
    print("\n--------------------------------------------\n");
    print("                   教学秘书系统               \n\n");
    print("                  1.创建课程表                  \n");
    print("                  2.删除课程表                  \n");
    print("                  3.增加课程条目                \n");
    print("                  4.修改课程条目                \n");
    print("                  5.删除课程条目                \n");
    print("                  6.返回主菜单                  \n\n");
    print("请选择你要进行的操作: ");
    cin>>choice;
    switch(choice)
    {
        case 1:
            string id,name;
            print("请输入课程表号: ");
            cin>>id;
            _registrar.createSchedules(tsid,id);
            break;
        case 2:
            string id1;
            print("请输入你想删除的课程表号: ");
            cin>>id1;
            _registrar.removeSchedules(tsid,id1);
            break;
        case 3:
            string sid,eid,time,room,tid,cid;
            print("请输入课程表编号：");
            cin>>sid;
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
            _registrar.createScheduleEntrys(tsid,sid,eid,time,room,tid)
            break;
        case 4:
            string id2;
            print("请输入你要修改的课程条目编号: ");
            cin>>id2;
            print("-------------课程条目:{}----------\n\n",);
            print("             1.修改时间           \n");
            print("             2.修改地点           \n");
            print("             3.修改授课老师        \n");
            print("             4.修改课程编号        \n");
            print("             5.返回上一页          \n");
            int choice1;
            print("请选择你要进行的操作: ");
            cin>>choice1;
            switch(choice1)
            {
                case 1:
                    string time2;
                    print("请输入你要修改的时间：");
                    cin>>time2;
                    _registrar.modifyEntrytime(id2,time2);
                    break;
                case 2:
                    string room2;
                    print("请输入你要修改的地点： ");
                    cin>>room2;
                    _registrar.modifyEntryroom(id2,room2);
                    break;
                case 3:
                    string tid2;
                    print("请输入你要修改的教师编号：");
                    cin>>tid2;
                    _registrar.modifyEntryteacher(id2,tid2);
                    break;
                case 4:
                    string cid2;
                    print("请输入你要修改的课程编号：");
                    cin>>cid2;
                    _registrar.modifyEntrycourse(id2,cid2);
                    break;
                case 5:
                    print("返回上一页\n");
                    break;
                default:
                    print("输入无效，请重新选择!\n");
            }
            break;
        case 5:
            string id3;
            print("请输入你要删除的课程条目编号: ");
            cin>>id3;
            _registrar.removeScheduleEntrys(tsid,id3);
            break;
        case 6:
            print("返回主菜单\n");
            break;
        default:
            print("输入无效，请重新选择!\n");
}
