/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
file name: link_list.h

������
������ֻ��һ��ͷ�ڵ㣨������Ч��data������
list_ptr_->next == NULL
��Ч����list_ptr_ == NULL

include both C and C++ version��
for the C++ version, ģ���� is used, and
for the C version, the functions are defined as inline.

InitList()
    ����������
ClearList()
    �����������ͷ�ڵ㣩��Ҫ���������
DestroyList()
    ��������������ͷ�ڵ㣩
empty() const
	�ж������Ƿ�Ϊ��
HeadInsert(T node_data)
    ͷ�˲���
TailInsert(T node_data)
	β�˲���
AscendingInsert(T node_data)
	�������
PosSearch(int pos)
	Ѱ��ָ��λ��
DataSearch(T data)
	Ѱ��ָ��ֵ��λ��
PosInsert(int pos, T node_data)
	ָ��λ�ò���
PosDelete(int pos)
    ָ��λɾ��
DataDelete(T data)
    ָ������ֵ�Ľڵ�ɾ��
Travel(int(T&))
    �������ʸ��ڵ�

***************************************************/
#ifndef _LINK_LIST_H
#define _LINK_LIST_H

#include "cnode.h"


#ifdef __cplusplus

template<typename T> //T�������нڵ�Ԫ�������������
class LinkList{
// friend std::ostream &operator<<(std::ostream&, const LinkList<T>&);
public:
    // constructors & destructor
    LinkList(){}
    ~LinkList(){}

    //general member function
    int InitList();  //��ʼ��������
    int ClearList();
    int DestroyList();

    int HeadInsert(T);
    int TailInsert(T);
    int AscendingInsert(T);
    int PosInsert(int, T);

    int PosDelete(int);
    int DataDelete(T);

    int Travel(int(T&));

protected:
	using ListPtr = LNode<T>*;
	LNode<T>* PosSearch(int pos);
	LNode<T>* DataSearch(T);

public:
    //input/output function
    int empty()const;

    //data member
    ListPtr list_ptr_;
    LNode<T>* tail_ = NULL;

};



//template<typename T>
//int DeleteThis(LinkList<T>::LNode*& node_ptr); //ɾ����ǰ�ڵ㲢������һ�ڵ�

#include <assert.h>
#define NEXT(ptr) ((ptr)=(ptr)->next)

template <typename T>
int LinkList<T>::InitList()
{  //����������
    tail_ = list_ptr_ = new LNode<T>;
    return 0;
}

template <typename T>
int LinkList<T>::ClearList()
{  //�����������ͷ�ڵ㣩��Ҫ���������
    assert(list_ptr_);
    LNode<T>* p = list_ptr_->next;
    list_ptr_->next = NULL;
    LNode<T>* q;
    while(p){
        q = p->next;
        delete p;
        p = q;
    }
    return 0;
}

template <typename T>
int LinkList<T>::DestroyList()
{ //��������������ͷ�ڵ㣩
    if (list_ptr_){
        ClearList();
        delete list_ptr_;
        list_ptr_ = NULL;
    }
    return 0;
}

template <typename T>
int LinkList<T>::empty() const
{ //�ж������Ƿ�Ϊ��
    return (list_ptr_==NULL);
}

template <typename T>
int LinkList<T>::HeadInsert(T node_data)
{ //ͷ�˲���
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    p->InsertNext(node_data);
    if (p->next->next == NULL)
        tail_ = p->next;
    return 0;
}

template <typename T>
int LinkList<T>::TailInsert(T node_data)
{ //β�˲���
    assert (list_ptr_);
    tail_->InsertNext(node_data);
    tail_ = tail_->next;
    return 0;
}

template <typename T>
int LinkList<T>::AscendingInsert(T node_data)
{ //�������
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    while (p->next && (node_data > p->next->data)){
        NEXT(p);
    }
    p->InsertNext(node_data);
    if (p->next->next == NULL)
        tail_ = p->next;
    return 0;
}

template <typename T>
LNode<T>* LinkList<T>::PosSearch(int pos)
{ //Ѱ��ָ��λ��
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    while (p->next && pos>1){
        NEXT(p);
        pos--;
    }
    if (pos>1) //bad position
        return NULL;
    return p;
}

template <typename T>
LNode<T>* LinkList<T>::DataSearch(T data)
{ //Ѱ��ָ��ֵ��λ��
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    while (p->next && !equal(p->next->data, data)){
        NEXT(p);
    }
    if (p->next ==  NULL) //no such data
        return NULL;
    return p;
}

template <typename T>
int LinkList<T>::PosInsert(int pos, T node_data)
{ //ָ��λ�ò���
    assert (list_ptr_);
    LNode<T>* p = PosSearch(pos);
    if (p == NULL) //bad position
        return -1; 
    p->InsertNext(node_data);
    if (p->next->next == NULL)
        tail_ = p->next;
    return 0;
}

template <typename T>
int LinkList<T>::PosDelete(int pos)
{ //ָ��λɾ��
    assert (list_ptr_);
    LNode<T>* p = PosSearch(pos);
	if (p == NULL) //bad position
		return -1;
    p->DeleteNext();
    if (p->next == NULL)
        tail_ = p;
    return 0;
}

template <typename T>
int LinkList<T>::DataDelete(T data)
{ //ָ������ֵ�Ľڵ�ɾ��
    assert (list_ptr_);
    LNode<T>* p = DataSearch(data);
    if (p == NULL) //no such data 
        return -1;
    p->DeleteNext();
    if (p->next == NULL)
        tail_ = p;
    return 0;
}


//template <typename T>
//std::ostream LinkList<T>::&operator<<(std::ostream& os, const LinkList<T>& list)
//{
//    assert (list.list_ptr_);
//    LNode<T>* p = list.list_ptr_;
//    while (p->next){
//        NEXT(p);
//        os << p->data;
//    }
//    return os;
//}

template <typename T>
int LinkList<T>::Travel(int func(T&))
{ //�������ʸ��ڵ�
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    while (p->next){
        NEXT(p);
        func(p->data);
    }
    return 0;
}

#else  // nef __cplusplus

/**************************************************************
C version below

**************************************************************/

typedef LNode* ListPtr;

typedef struct{
    ListPtr list_ptr_;
    LNode* tail_;
}LinkList;

int InitList(LinkList*);  //��ʼ��������
int ClearList(LinkList*);
int DestroyList(LinkList*);
int empty(LinkList*);

int HeadInsert(LinkList*, type_T);
int TailInsert(LinkList*, type_T);
int AscendingInsert(LinkList*, type_T);
int PosInsert(LinkList*, int, type_T);

LNode* PosSearch(LinkList*, int pos);
LNode* DataSearch(LinkList*, type_T);

int PosDelete(LinkList*, int);
int DataDelete(LinkList*, type_T);

int Travel(LinkList* ,int(type_T*));


#define NEXT(ptr) ((ptr)=(ptr)->next)

/************** declaration **************/
//template<typename T>
//int DeleteThis(LinkList<T>::LNode*& node_ptr); //ɾ����ǰ�ڵ㲢������һ�ڵ�

/************** definition **************/
#include <stdio.h>
#include <assert.h>

inline int InitList(LinkList* this)
{  //����������
    this->tail_ = this->list_ptr_ = (LNode*)malloc(sizeof(LNode));//new LNode<T>;
	this->tail_->next = NULL;
    return 0;
}

inline int ClearList(LinkList* this)
{  //�����������ͷ�ڵ㣩��Ҫ���������
    assert(this->list_ptr_);
    LNode* p = this->list_ptr_->next;
	LNode* q;
	this->list_ptr_->next = NULL;
    while(p){
        q = p->next;
        free(p);
        p = q;
    }
    return 0;
}

inline int DestroyList(LinkList* this)
{ //��������������ͷ�ڵ㣩
    if (this->list_ptr_){
        ClearList(this);
        free(this->list_ptr_);
        this->list_ptr_ = NULL;
    }
    return 0;
}

inline int empty(LinkList* this)
{ //�ж������Ƿ�Ϊ��
    return (this->list_ptr_==NULL);
}

inline int HeadInsert(LinkList* this, type_T node_data)
{ //ͷ�˲���
    assert (this->list_ptr_);
    LNode* p = this->list_ptr_;
    InsertNext(p, node_data);
    if (p->next->next == NULL)
        this->tail_ = p->next;
    return 0;
}

inline int TailInsert(LinkList* this, type_T node_data)
{ //β�˲���
    assert (this->list_ptr_);
    InsertNext(this->tail_, node_data);
    this->tail_ = this->tail_->next;
    return 0;
}

inline int AscendingInsert(LinkList* this, type_T node_data)
{ //�������
    assert (this->list_ptr_);
    LNode* p = this->list_ptr_;
    while (p->next && greater(node_data, p->next->data)){
        NEXT(p);
    }
    InsertNext(p, node_data);
    if (p->next->next == NULL)
        this->tail_ = p->next;
    return 0;
}

inline int PosInsert(LinkList* this, int pos, type_T node_data)
{ //ָ��λ�ò��룬�����ռ�ݸ�λ��
	assert(this->list_ptr_);
	LNode* p = PosSearch(this, pos);
	if (p == NULL)
		return -1; //bad position
	InsertNext(p, node_data);
	if (p->next->next == NULL)
		this->tail_ = p->next;
	return 0;
}

inline LNode* PosSearch(LinkList* this, int pos)
{ //Ѱ��ָ��λ��,����ֵ��nextָ���λ�ã�Ҫ��λ�ô���0
    assert(this->list_ptr_);
	assert(pos > 0);
    LNode* p = this->list_ptr_;
    while (p->next && pos>1){
        NEXT(p);
        pos--;
    }
    if (pos>1) //bad position
        return NULL;
    return p;
}

inline LNode* DataSearch(LinkList* this, type_T data)
{ //Ѱ��ָ��ֵ��λ��,����ֵ��nextָ���λ��
    assert (this->list_ptr_);
    LNode* p = this->list_ptr_;
    while (p->next && !equal(p->next->data, data)){
        NEXT(p);
    }
    if (p->next ==  NULL){
        printf("no such data\n");
        return NULL;
    }
    return p;
}

inline int PosDelete(LinkList* this, int pos)
{ //ָ��λɾ��
    assert (this->list_ptr_);
    LNode* p = PosSearch(this, pos);
    if (p == NULL || p->next == NULL)
        return -1; //bad position
    DeleteNext(p);
    if (p->next == NULL)
        this->tail_ = p;
    return 0;
}

inline int DataDelete(LinkList* this, type_T data)
{ //ָ������ֵ�Ľڵ�ɾ��
    assert (this->list_ptr_);
    LNode* p = DataSearch(this, data);
    if (p == NULL)
        return -1; //no such data
    DeleteNext(p);
    if (p->next == NULL)
        this->tail_ = p;
    return 0;
}

inline int Travel(LinkList* this, int func(type_T*))
{ //�������ʸ��ڵ�
    assert (this->list_ptr_);
    LNode* p = this->list_ptr_;
    while (p->next){
        NEXT(p);
        func(&p->data);
    }
    return 0;
}



#endif // __cplusplus

#endif // _LINK_LIST_H
