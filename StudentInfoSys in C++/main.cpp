/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
project name: StudentInfoSys
file name: main.cpp

学生信息系统菜单界面
int PrintManu()
输出菜单
***************************************************/
#include <iostream>
#include "../include/stu_info_sys.h"

using namespace std;

#define REQUIRE_EXIST_LIST if(!stu_info.Exist()){ \
                               printf("Student Information chart doesn't exist.\n"); \
                               break;}
#define REQUIRE_N_EXIST_LIST if(stu_info.Exist()){ \
                                 printf("Student Information chart already exists.\n"); \
                                 break;}

int PrintMenu()
{
static const char menu[] = "\
0.退出\n\
1. 创建学生记录链表\n\
2. 打印全部学生记录\n\
3. 插入一条新的学生记录\n\
4. 删除一条学生记录\n\
5. 按学号查找学生记录\n\
6. 统计\n\
7. 销毁学生链表\n\
8. 将学生信息写入磁盘文件\n\
";
    cout << menu << endl;
	return 0;
}

int main()
{
	int fun, fun1;
	StuInfoSys stu_info;
	do {
		PrintMenu();
		cin >> fun;
		switch (fun) {
		case 1: { //创建学生记录链表
			REQUIRE_N_EXIST_LIST;
			stu_info.InitList();
			cout << "	1）头插法	2）尾插法	3）创建按学号有序链表	4）打开学生信息文件创建链表" << endl;
			cin >> fun1;
			stu_info.Creat(fun1);
			cout << "Creat success:\n" << stu_info << endl;
		}break;
		case 2: { //打印全部学生记录
			REQUIRE_EXIST_LIST;
			cout << stu_info << endl;
		}break;
		case 3: { //插入一条新的学生记录
			REQUIRE_EXIST_LIST;
			cout << "	1）按指定位序插入	2）在有序链表中插入" << endl;
			cin >> fun1;
			if (stu_info.InsertNode(fun1))
				cout << "Insert fail\n";
			else
				cout << "Insert success:\n" << stu_info << endl;
		}break;
		case 4: { //按删除一条学生记录
			REQUIRE_EXIST_LIST;
			cout << "	1）删除指定位置的记录	2）删除指定学号的记录" << endl;
			cin >> fun1;
			if (stu_info.DeleteNode(fun1))
				cout << "Delete fail\n";
			else
				cout << "Delete success:\n" << stu_info << endl;
		}break;
		case 5: { //按学号查找学生记录
			REQUIRE_EXIST_LIST;
			stu_info.FindNode();
		}break;
		case 6: { //统计
			REQUIRE_EXIST_LIST;
			stu_info.Statistic();

		}break;
		case 7: { //销毁学生链表
			REQUIRE_EXIST_LIST;
			stu_info.DestroyList();
			cout << "Destroy success\n";
		}break;
		case 8: { //将学生信息写入磁盘文件
			cout << "暂不支持文件操作";
		}break;
		}
	} while (fun);
	return 0;
}
