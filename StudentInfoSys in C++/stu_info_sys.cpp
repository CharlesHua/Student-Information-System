/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
project name: StudentInfoSys
file name: stu_info_sys.cpp

Creat(int)
    �����������ѡ���Ӧ��ʽ��������
InsertNode(int)
    �����������ѡ���Ӧ��ʽ����ڵ�
DeleteNode(int)
    �����������ѡ���Ӧ��ʽɾ���ڵ�
FindNode()
    Ѱ�ҽ��
Statistic()
    ͳ������ڵ����������
Exist()
    �ж������Ƿ����
***************************************************/
#include <iostream>
#include "../include/stu_info_sys.h"

using namespace std;

#ifndef KEY_VALUE
#define KEY_VALUE id
int operator>(const NodeData& data1, const NodeData& data2)
{
    if (data1.KEY_VALUE > data2.KEY_VALUE)
        return 1;
    else
        return 0;
}
#undef KEY_VALUE
#endif // KEY_VALUE

#ifndef KEY_VALUE
#define KEY_VALUE id
int equal(const NodeData& data1, const NodeData& data2)
{
    if (data1.KEY_VALUE == data2.KEY_VALUE)
        return 1;
    else
        return 0;
}
#undef KEY_VALUE
#endif // KEY_VALUE

std::ostream &operator<<(std::ostream &os, const NodeData& data)
{
    os << data.id << "  " << data.score << "\n";
    return os;
}


/**************************************************************************/


std::ostream &operator<<(std::ostream& os, const StuInfoSys& list)
{
    assert (list.list_ptr_);
    ListNode* p = list.list_ptr_;
    while (p->next){
        NEXT(p);
        os << p->data;
    }
    return os;
}

int StuInfoSys::Creat(int func1)
{
    int id, score;
    int (StuInfoSys::*Insert[3])(NodeData) = {&StuInfoSys::HeadInsert,
		                                      &StuInfoSys::TailInsert,
		                                      &StuInfoSys::AscendingInsert};
    func1--;
    switch (func1) {
        case 0:   //ͷ�巨
        case 1:   //β�巨
        case 2:{ //ѧ������
            cout << "��������������ѧ�źͳɼ�,��ѧ��0����" << endl;
            do{
                cin >> id >> score;
                if (id != 0){
                    (this ->* Insert[func1])(NodeData(id, score));
                    cout << "\tmake node success\n";
                }
            }while (id);
        }break;
		case 3: { //�ļ�����
			cout << "�ݲ�֧���ļ�����\n";
		}break;
    }
    return 0;
}

int StuInfoSys::InsertNode(int func1)
{  //�����¼
    int id, score;
    switch (func1) {
        case 1:{   //ָ��λ��
            int pos;
            cout << "����������ѧ�š��ɼ���Ҫ�����λ��" << endl;
            cin >> id >> score >> pos;
			if (pos <= 0 || PosInsert(pos, NodeData(id, score))) {
				cout << "bad position\n";
				return -1;
			}
        }break;
        case 2:{
            cout << "����������ѧ�źͳɼ�" << endl;
            cin >> id >> score;
            AscendingInsert(NodeData(id, score));
            cout << "\tmake node success\n";
        }break;
    }
    return 0;
}

int StuInfoSys::DeleteNode(int func1)
{  //ɾ����¼
    int id;
    switch (func1) {
        case 1:{  //ָ��λ��
            int pos;
            cout << "������λ��" << endl;
            cin  >> pos;
            if (pos <= 0 || PosDelete(pos)) {
				printf("bad position\n");
				return -1;
			}
        }break;
        case 2:{ //ָ��ѧ��
            cout << "������ѧ��" << endl;
            cin >> id;
            if (DataDelete(NodeData(id, 0))) {
				printf("no this id\n");
				return -1;
			}
        }break;
    }
    return 0;
}

int StuInfoSys::FindNode()
{  //���Ҽ�¼
    int id;
    cout << "������ѧ��" << endl;
    cin >> id;
    ListNode* p = DataSearch(NodeData(id, NULL));
    if (p)
        cout << p->next->data << endl;
    else
		cout << "no this id\n";
    return 0;
}


int StuInfoSys::Statistic()
{
    assert (list_ptr_);
    ListPtr p = list_ptr_;
    int tot_people = 0;
    int tot_score = 0;
    int max_score = 0;
    int tot_failed = 0;
    static int pass_line = 60;
	cout << "�����뼰������� ";
	cin >> pass_line;
    while (p->next){
        p = p->next;
        // func(p->data);
        tot_people++;
        tot_score += p->data.score;
        if (p->data.score > max_score)
            max_score = p->data.score;
        if (p->data.score < pass_line)
            tot_failed++;
    }
    std::cout << "\t������ = " << tot_people << std::endl
              << "\tƽ���� = " << (float)tot_score/tot_people << std::endl
              << "\t��߷� = " << max_score << std::endl
              << "\t���������� = " << tot_failed << std::endl;
    return 0;
}

int StuInfoSys::Exist()
{
	return !empty();
}

//int tot = 0;
//    int add(NodeData& data)
//    {
//        return tot += data.score;
//    }
//
//int StuInfoSys::getAveScore()
//{
//    tot = 0;
//    Travel(add);
//    std::cout << tot << std::endl;
//}

//int printdata(NodeData& data)
//{
//    std::cout << data.id <<" " << data.score << std::endl;
//    return 0;
//}
//
//int StuInfoSys::printList()
//{
//    Travel(printdata);
//    return 0;
//}

