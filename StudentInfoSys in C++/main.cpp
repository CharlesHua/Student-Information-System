/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
project name: StudentInfoSys
file name: main.cpp

ѧ����Ϣϵͳ�˵�����
int PrintManu()
����˵�
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
		case 1: { //����ѧ����¼����
			REQUIRE_N_EXIST_LIST;
			stu_info.InitList();
			cout << "	1��ͷ�巨	2��β�巨	3��������ѧ����������	4����ѧ����Ϣ�ļ���������" << endl;
			cin >> fun1;
			stu_info.Creat(fun1);
			cout << "Creat success:\n" << stu_info << endl;
		}break;
		case 2: { //��ӡȫ��ѧ����¼
			REQUIRE_EXIST_LIST;
			cout << stu_info << endl;
		}break;
		case 3: { //����һ���µ�ѧ����¼
			REQUIRE_EXIST_LIST;
			cout << "	1����ָ��λ�����	2�������������в���" << endl;
			cin >> fun1;
			if (stu_info.InsertNode(fun1))
				cout << "Insert fail\n";
			else
				cout << "Insert success:\n" << stu_info << endl;
		}break;
		case 4: { //��ɾ��һ��ѧ����¼
			REQUIRE_EXIST_LIST;
			cout << "	1��ɾ��ָ��λ�õļ�¼	2��ɾ��ָ��ѧ�ŵļ�¼" << endl;
			cin >> fun1;
			if (stu_info.DeleteNode(fun1))
				cout << "Delete fail\n";
			else
				cout << "Delete success:\n" << stu_info << endl;
		}break;
		case 5: { //��ѧ�Ų���ѧ����¼
			REQUIRE_EXIST_LIST;
			stu_info.FindNode();
		}break;
		case 6: { //ͳ��
			REQUIRE_EXIST_LIST;
			stu_info.Statistic();

		}break;
		case 7: { //����ѧ������
			REQUIRE_EXIST_LIST;
			stu_info.DestroyList();
			cout << "Destroy success\n";
		}break;
		case 8: { //��ѧ����Ϣд������ļ�
			cout << "�ݲ�֧���ļ�����";
		}break;
		}
	} while (fun);
	return 0;
}
