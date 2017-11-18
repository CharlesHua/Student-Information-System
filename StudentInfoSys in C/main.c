/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.16
project name: StudentInfoSys
file name: main.c

学生信息系统菜单界面
int PrintManu()
输出菜单
***************************************************/
#pragma warning(disable:4996)
// so that one can use scanf, rather than have to use scanf_s

#include <stdio.h>
#include "../include/stu_info_sys.h"

#define REQUIRE_EXIST_LIST if(!Exist(&stu_info)){ \
                               printf("Student Information chart doesn't exist.\n"); \
                               break;}
#define REQUIRE_N_EXIST_LIST if(Exist(&stu_info)){ \
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
    printf("%s\n", menu);
    return 0;
}


int main()
{
    int fun, fun1;
	StuInfoSys stu_info;
    do{
        PrintMenu();
        scanf("%d", &fun);
        switch (fun) {
            case 1:{ //创建学生记录链表
				REQUIRE_N_EXIST_LIST;
				InitList(&stu_info);
                printf("	1）头插法	2）尾插法	3）创建按学号有序链表	4）打开学生信息文件创建链表\n");
                scanf("%d", &fun1);
				if (Creat(&stu_info, fun1)) {
					printf("Creat fail\n");
					DestroyList(&stu_info);
				}
				else{
					printf("Creat success:\n");
					print_list(&stu_info);
				}
            }break;
            case 2:{ //打印全部学生记录
				REQUIRE_EXIST_LIST;
				print_list(&stu_info);
			}break;
            case 3:{ //插入一条新的学生记录
				REQUIRE_EXIST_LIST;
                printf("	1）按指定位序插入	2）在有序链表中插入\n");
                scanf("%d", &fun1);
				if (InsertNode(&stu_info, fun1))
					printf("Insert fail\n");
				else {
					printf("Insert success:\n");
					print_list(&stu_info);
				}
			}break;
            case 4:{ //按删除一条学生记录
				REQUIRE_EXIST_LIST;
                printf("	1）删除指定位置的记录	2）删除指定学号的记录\n");
                scanf("%d", &fun1);
				if (DeleteNode(&stu_info, fun1))
					printf("Delete fail");
				else {
					printf("Delete success:\n");
					print_list(&stu_info);
				}
			}break;
            case 5:{ //按学号查找学生记录
				REQUIRE_EXIST_LIST;
                FindNode(&stu_info);
            }break;
            case 6:{ //统计
				REQUIRE_EXIST_LIST;
                Statistic(&stu_info);
            }break;
            case 7:{ //销毁学生链表
				REQUIRE_EXIST_LIST;
                DestroyList(&stu_info);
				printf("Destroy success\n");
            }break;
            case 8:{ //将学生信息写入磁盘文件
				printf("	1）重写(新建)学生文件	2）追加学生文件	3）清空学生文件\n");
				scanf("%d", &fun1);
                if (fun1 == 1 || fun1 == 2)
					REQUIRE_EXIST_LIST;
				if (Write2File(&stu_info, fun1))
					printf("Write to file fail.\n");
				else
					printf("Write to file success\n");
            }break;
        }
    }while(fun);
    return 0;
}
