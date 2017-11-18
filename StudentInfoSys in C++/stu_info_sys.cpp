/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
project name: StudentInfoSys
file name: stu_info_sys.cpp

Creat(int)
    根据输入参数选择对应方式生成链表
InsertNode(int)
    根据输入参数选择对应方式插入节点
DeleteNode(int)
    根据输入参数选择对应方式删除节点
FindNode()
    寻找结点
Statistic()
    统计链表节点域相关数据
Exist()
    判断链表是否存在
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
        case 0:   //头插法
        case 1:   //尾插法
        case 2:{ //学号升序
            cout << "请依次输入各项的学号和成绩,以学号0结束" << endl;
            do{
                cin >> id >> score;
                if (id != 0){
                    (this ->* Insert[func1])(NodeData(id, score));
                    cout << "\tmake node success\n";
                }
            }while (id);
        }break;
		case 3: { //文件输入
			cout << "暂不支持文件操作\n";
		}break;
    }
    return 0;
}

int StuInfoSys::InsertNode(int func1)
{  //插入记录
    int id, score;
    switch (func1) {
        case 1:{   //指定位置
            int pos;
            cout << "请依次输入学号、成绩和要插入的位置" << endl;
            cin >> id >> score >> pos;
			if (pos <= 0 || PosInsert(pos, NodeData(id, score))) {
				cout << "bad position\n";
				return -1;
			}
        }break;
        case 2:{
            cout << "请依次输入学号和成绩" << endl;
            cin >> id >> score;
            AscendingInsert(NodeData(id, score));
            cout << "\tmake node success\n";
        }break;
    }
    return 0;
}

int StuInfoSys::DeleteNode(int func1)
{  //删除记录
    int id;
    switch (func1) {
        case 1:{  //指定位置
            int pos;
            cout << "请输入位置" << endl;
            cin  >> pos;
            if (pos <= 0 || PosDelete(pos)) {
				printf("bad position\n");
				return -1;
			}
        }break;
        case 2:{ //指定学号
            cout << "请输入学号" << endl;
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
{  //查找记录
    int id;
    cout << "请输入学号" << endl;
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
	cout << "请输入及格分数线 ";
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
    std::cout << "\t总人数 = " << tot_people << std::endl
              << "\t平均分 = " << (float)tot_score/tot_people << std::endl
              << "\t最高分 = " << max_score << std::endl
              << "\t不及格人数 = " << tot_failed << std::endl;
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

