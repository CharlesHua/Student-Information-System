/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
project name: StudentInfoSys
file name: stu_info_sys.h

ѧ����Ϣϵͳ
include both C and C++ version��
for the C++ version, ģ���� is used, and this file work with stu_info_sys.cpp
for the C version, the functions are defined in the stu_info_sys.c

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
#ifndef _STU_INFO_SYS_H
#define _STU_INFO_SYS_H

#ifdef __cplusplus

#include <iostream>
#include "link_list.h"


struct NodeData{
friend int operator>(const NodeData&, const NodeData&);
friend int equal(const NodeData&, const NodeData&);
friend std::ostream &operator<<(std::ostream&, const NodeData&);
	NodeData(){};
    NodeData(int new_id, int new_score):id(new_id),score(new_score){}
    int id;  //ѧ��
    int score;  //����
};


//the following two lines are equal
typedef LNode<NodeData> ListNode;
//using PolNode = LNode<NodeData>;

class StuInfoSys: public LinkList<NodeData>{
friend std::ostream &operator<<(std::ostream&, const StuInfoSys&);
public :
    // constructors & destructor
    StuInfoSys(){};
    ~StuInfoSys(){}

    //general member function
    int Creat(int);
    int InsertNode(int);
    int DeleteNode(int);
    int FindNode();
    int Statistic();

private :

public :
    //input/output function
    int printList() ;
	int Exist();

};

#else  // nef __cplusplus

/**************************************************************
C version below
******************* *******************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct NodeData{
    int id;  //ѧ��
    int score;  //����
}Data;
//one should define the struct NodeData, before including the link_list.h
#include "link_list.h"

typedef LinkList StuInfoSys;
//StuInfoSys stu_info;

//���캯��
struct NodeData NodeData(int new_id, int new_score);

int Creat(StuInfoSys* this, int fun1);
int InsertNode(StuInfoSys* this, int fun1);
int DeleteNode(StuInfoSys* this, int fun1);
int FindNode(StuInfoSys* this);
int Statistic(StuInfoSys* this);
int Exist(StuInfoSys* this);

//�������
int print_data(Data*);
int print_list(StuInfoSys*);
int Write2File(StuInfoSys* this, int fun1);


#endif // __cplusplus

#endif // _STU_INFO_SYS_H
