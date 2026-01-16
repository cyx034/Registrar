export module ui;
import std;
import registrar;

using std::print;
using std::cin;

export class Ui
{
public:
    Ui();//构造函数
    void welcomeui();
    void studentui();
    void teacherui();
    void teachingsecretaryui();

};

void Ui::welcomeui()
{
    int choice;
    while(choice != 0){
        print("\n-------------------------------------------\n");
        print("                  欢迎来到选课系统              \n\n");
        print("                  1.学生登录                   \n");
        print("                  2.教师登录                   \n");
        print("                  3.教务秘书登录                \n");
        print("                  0.退出系统                   \n\n");
        print("请选择登录身份: ");
        cin>>choice;
        switch(choice)
        {
            case 1:
                studentui();
                break;
            case 2:
                teacherui();
                break;            print("课程表删除成功！\n");
            break;
            case 3:
                teachingsecretaryui();
                break;
            case 4:
                print("感谢使用，再见！\n");
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
    print("                     学生系统                  \n\n");
    print("                  1.选课功能                   \n");
    print("                  2.退课功能                   \n");
    //print("                  3.查看课表                   \n");
    //print("                  4.查看成绩                   \n");
    print("                  0.返回主菜单                  \n\n");
    print("请选择你要进行的操作: ");
    cin>>choice;
    switch(choice)
    {
        case 1:
            //打印所有课程信息
            string cid;
            print("请输入要选择的课程号: ");
            cin>>cid;

            break;
        case 2:
            string cid1;
            print("请输入要退选的课程号: ");
            cin>>cid1;

            break;
        case 0:
            print("返回主菜单\n");
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
    print("                  0.返回主菜单                  \n\n");
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
            print("请输入该学生的成绩: ");
            cin>>grade;

            break;
        case 2:
            //查看教师课表

            break;
        case 0:
            print("返回主菜单\n");
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
    print("                     教学秘书系统               \n\n");
    print("                  1.创建课程表                  \n");
    print("                  2.删除课程表                  \n");
    print("                  3.增加课程条目                \n");
    print("                  4.修改课程条目                \n");
    print("                  5.删除课程条目                \n");
    print("                  0.返回主菜单                  \n\n");
    print("请选择你要进行的操作: ");
    cin>>choice;
    switch(choice)
    {
        case 1:
            string id,name;
            print("请输入课程表号: ");
            cin>>id;
            print("请输入课程表名: ");
            cin>>name;

            break;
        case 2:
            string id1;
            print("请输入你想删除的课程表号: ");
            cin>>id1;
            //具体操作或结果

            break;
        case 3:
            string scid,time,room,max,current,tid,cid;
            print("请输入课程条目编号:");
            cin>>scid;
            print("请输入课程时间:");
            cin>>time;
            print("请输入所在教室:");
            cin>>room;
            print("请输入最大上课人数:");
            cin>>max;
            print("请输入当前上课人数:");
            cin>>current;
            print("请输入教师编号:");
            cin>>tid;
            print("请输入课程编号:");
            cin>>cid;

            break;
        case 4:
            string id2;
            print("请输入你要修改的课程条目编号: ");
            //具体修改项目

            break;
        case 5:
            string id3;
            print("请输入你要删除的课程条目编号: ");
            cin>>id3;

            break;
        case 0:
            print("返回主菜单\n");
        default:
            print("输入无效，请重新选择!\n");
}
