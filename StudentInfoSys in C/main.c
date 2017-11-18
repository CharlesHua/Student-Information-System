/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.16
project name: StudentInfoSys
file name: main.c

ѧ����Ϣϵͳ�˵�����
int PrintManu()
����˵�
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
0.�˳�\n\
1. ����ѧ����¼����\n\
2. ��ӡȫ��ѧ����¼\n\
3. ����һ���µ�ѧ����¼\n\
4. ɾ��һ��ѧ����¼\n\
5. ��ѧ�Ų���ѧ����¼\n\
6. ͳ��\n\
7. ����ѧ������\n\
8. ��ѧ����Ϣд������ļ�\n\
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
            case 1:{ //����ѧ����¼����
				REQUIRE_N_EXIST_LIST;
				InitList(&stu_info);
                printf("	1��ͷ�巨	2��β�巨	3��������ѧ����������	4����ѧ����Ϣ�ļ���������\n");
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
            case 2:{ //��ӡȫ��ѧ����¼
				REQUIRE_EXIST_LIST;
				print_list(&stu_info);
			}break;
            case 3:{ //����һ���µ�ѧ����¼
				REQUIRE_EXIST_LIST;
                printf("	1����ָ��λ�����	2�������������в���\n");
                scanf("%d", &fun1);
				if (InsertNode(&stu_info, fun1))
					printf("Insert fail\n");
				else {
					printf("Insert success:\n");
					print_list(&stu_info);
				}
			}break;
            case 4:{ //��ɾ��һ��ѧ����¼
				REQUIRE_EXIST_LIST;
                printf("	1��ɾ��ָ��λ�õļ�¼	2��ɾ��ָ��ѧ�ŵļ�¼\n");
                scanf("%d", &fun1);
				if (DeleteNode(&stu_info, fun1))
					printf("Delete fail");
				else {
					printf("Delete success:\n");
					print_list(&stu_info);
				}
			}break;
            case 5:{ //��ѧ�Ų���ѧ����¼
				REQUIRE_EXIST_LIST;
                FindNode(&stu_info);
            }break;
            case 6:{ //ͳ��
				REQUIRE_EXIST_LIST;
                Statistic(&stu_info);
            }break;
            case 7:{ //����ѧ������
				REQUIRE_EXIST_LIST;
                DestroyList(&stu_info);
				printf("Destroy success\n");
            }break;
            case 8:{ //��ѧ����Ϣд������ļ�
				printf("	1����д(�½�)ѧ���ļ�	2��׷��ѧ���ļ�	3�����ѧ���ļ�\n");
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
