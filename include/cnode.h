/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
file name: cnode.h

�����ڵ�����ջ�����еȵĽ��
include both C and C++ version

For the C++ version, ģ���� is used, and
for the C version, the functions are defined as inline.

DeleteNext()
    ɾ���ýڵ����һ���ڵ�
InsertNext(T node_data)
    �ڸýڵ�֮���������Ϊnode_data���½ڵ�
***************************************************/
#ifndef _CNODE_H
#define _CNODE_H


#ifdef __cplusplus

template <typename T>
class LNode{
public:
    // constructors & destructor
    LNode(){};
    LNode(T& new_data):data(new_data){}
    LNode(T& new_data, LNode* new_next):data(new_data),next(new_next){}

    //general function member
    int DeleteNext();
    int InsertNext(T node_data);

    //data member
    T data;
    LNode *next = NULL;
};

/**
template <typename T>
LNode<T>::LNode(){
    memset(&data, 0, sizeof(data));
}
*/

template <typename T>
int LNode<T>::DeleteNext()
{ //ɾ���ýڵ����һ���ڵ�
    if (next){
        LNode* q = next;
        next = q->next;
        delete q;
    }
    return 0;
}

template <typename T>
int LNode<T>::InsertNext(T node_data)
{ //�ڸýڵ�֮���������Ϊnode_data���½ڵ�
    next = new LNode(node_data, next);
    return 0;
}

#else  // nef __cplusplus

/**************************************************************
C version below

One shoule define the struct NodeData before this file was included.

**************************************************************/

//�ڵ�������򲿷�
typedef struct NodeData type_T;
int greater(const type_T, const type_T);
int equal(const type_T, const type_T);

//�ڵ㲿��
typedef struct Node{
//   LNode(T& new_data, LNode* new_next):data(new_data),next(new_next){}
    type_T data;
    struct Node *next;// = NULL;
}LNode;

// using LNode = struct Node;


//constructors
LNode* new_LNode(type_T new_data, LNode* new_next);

int DeleteNext(LNode*);
int InsertNext(LNode* this, type_T node_data);


#include <stdlib.h>

inline LNode* new_LNode(type_T new_data, LNode* new_next)
{ //��̬����һ���ڵ㲢������ָ��
	LNode* q = (LNode*)malloc(sizeof(LNode));
	if (q) {
		q->data = new_data;
		q->next = new_next;
	}
	return q;
}


inline int DeleteNext(LNode* this)
{ //ɾ���ýڵ����һ���ڵ�
    if (this->next){
        LNode* q = this->next;
        this->next = q->next;
        free(q);
    }
    return 0;
}


inline int InsertNext(LNode* this, type_T node_data)
{ //�ڸýڵ�֮���������Ϊnode_data���½ڵ�
	this->next =  new_LNode(node_data, this->next);
	return 0;
}


#endif // __cplusplus

#endif // _CNODE_H
