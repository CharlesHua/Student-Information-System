/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.18
file name: link_list.h

单链表
空链表：只有一个头节点（不含有效的data）的链
list_ptr_->next == NULL
无效链表：list_ptr_ == NULL

include both C and C++ version，
for the C++ version, 模板类 is used, and
for the C version, the functions are defined as inline.

InitList()
    创建空链表
ClearList()
    清空链表（保留头节点），要求链表存在
DestroyList()
    销毁链表（不保留头节点）
empty() const
	判断链表是否为空
HeadInsert(T node_data)
    头端插入
TailInsert(T node_data)
	尾端插入
AscendingInsert(T node_data)
	升序插入
PosSearch(int pos)
	寻找指定位置
DataSearch(T data)
	寻找指定值的位置
PosInsert(int pos, T node_data)
	指定位置插入
PosDelete(int pos)
    指定位删除
DataDelete(T data)
    指定数据值的节点删除
Travel(int(T&))
    遍历访问各节点

***************************************************/
#ifndef _LINK_LIST_H
#define _LINK_LIST_H

#include "cnode.h"


#ifdef __cplusplus

template<typename T> //T是链表中节点元素数据域的类型
class LinkList{
// friend std::ostream &operator<<(std::ostream&, const LinkList<T>&);
public:
    // constructors & destructor
    LinkList(){}
    ~LinkList(){}

    //general member function
    int InitList();  //初始化空链表
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
//int DeleteThis(LinkList<T>::LNode*& node_ptr); //删除当前节点并返回下一节点

#include <assert.h>
#define NEXT(ptr) ((ptr)=(ptr)->next)

template <typename T>
int LinkList<T>::InitList()
{  //创建空链表
    tail_ = list_ptr_ = new LNode<T>;
    return 0;
}

template <typename T>
int LinkList<T>::ClearList()
{  //清空链表（保留头节点），要求链表存在
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
{ //销毁链表（不保留头节点）
    if (list_ptr_){
        ClearList();
        delete list_ptr_;
        list_ptr_ = NULL;
    }
    return 0;
}

template <typename T>
int LinkList<T>::empty() const
{ //判断链表是否为空
    return (list_ptr_==NULL);
}

template <typename T>
int LinkList<T>::HeadInsert(T node_data)
{ //头端插入
    assert (list_ptr_);
    LNode<T>* p = list_ptr_;
    p->InsertNext(node_data);
    if (p->next->next == NULL)
        tail_ = p->next;
    return 0;
}

template <typename T>
int LinkList<T>::TailInsert(T node_data)
{ //尾端插入
    assert (list_ptr_);
    tail_->InsertNext(node_data);
    tail_ = tail_->next;
    return 0;
}

template <typename T>
int LinkList<T>::AscendingInsert(T node_data)
{ //升序插入
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
{ //寻找指定位置
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
{ //寻找指定值的位置
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
{ //指定位置插入
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
{ //指定位删除
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
{ //指定数据值的节点删除
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
{ //遍历访问各节点
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

int InitList(LinkList*);  //初始化空链表
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
//int DeleteThis(LinkList<T>::LNode*& node_ptr); //删除当前节点并返回下一节点

/************** definition **************/
#include <stdio.h>
#include <assert.h>

inline int InitList(LinkList* this)
{  //创建空链表
    this->tail_ = this->list_ptr_ = (LNode*)malloc(sizeof(LNode));//new LNode<T>;
	this->tail_->next = NULL;
    return 0;
}

inline int ClearList(LinkList* this)
{  //清空链表（保留头节点），要求链表存在
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
{ //销毁链表（不保留头节点）
    if (this->list_ptr_){
        ClearList(this);
        free(this->list_ptr_);
        this->list_ptr_ = NULL;
    }
    return 0;
}

inline int empty(LinkList* this)
{ //判断链表是否为空
    return (this->list_ptr_==NULL);
}

inline int HeadInsert(LinkList* this, type_T node_data)
{ //头端插入
    assert (this->list_ptr_);
    LNode* p = this->list_ptr_;
    InsertNext(p, node_data);
    if (p->next->next == NULL)
        this->tail_ = p->next;
    return 0;
}

inline int TailInsert(LinkList* this, type_T node_data)
{ //尾端插入
    assert (this->list_ptr_);
    InsertNext(this->tail_, node_data);
    this->tail_ = this->tail_->next;
    return 0;
}

inline int AscendingInsert(LinkList* this, type_T node_data)
{ //升序插入
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
{ //指定位置插入，插入后占据该位置
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
{ //寻找指定位置,返回值的next指向该位置，要求位置大于0
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
{ //寻找指定值的位置,返回值的next指向该位置
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
{ //指定位删除
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
{ //指定数据值的节点删除
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
{ //遍历访问各节点
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
