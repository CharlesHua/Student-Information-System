/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.17
project name: StudentInfoSys
file name: stu_info_sys.c

学生信息系统
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
#pragma warning(disable:4996)
// so that one can use scanf, rather than have to use scanf_s

#include <stdio.h>
#include "../include/stu_info_sys.h"


/***************************************************************************
NodeData related functions
****************************************************************************/
#ifndef KEY_VALUE
#define KEY_VALUE id
int greater(const type_T data1, const type_T data2)
{
    return (data1.KEY_VALUE > data2.KEY_VALUE);
}
#undef KEY_VALUE
#endif // KEY_VALUE

#ifndef KEY_VALUE
#define KEY_VALUE id
int equal(const type_T data1, const type_T data2)
{
    return (data1.KEY_VALUE == data2.KEY_VALUE);
}
#undef KEY_VALUE
#endif // KEY_VALUE


/***************************************************************************
StuInfoSys related functions
****************************************************************************/
struct NodeData NodeData(int new_id, int new_score)
{
	struct NodeData data = { new_id, new_score };
	return data;
}

int Creat(StuInfoSys* this, int func1)
{
    int id, score;
    int (*Insert[3])(StuInfoSys*, type_T) = {HeadInsert, TailInsert, AscendingInsert};
    func1--;
    switch (func1) {
        case 0:   //头插法
        case 1:   //尾插法
        case 2:{ //学号升序
		    printf("请依次输入各项的学号和成绩,以学号0结束\n");
            do{
                scanf("%d %d", &id, &score);
                if (id != 0){
                    (*Insert[func1])(this, NodeData(id, score));
	    			printf("\tmake node success\n");
                }
            }while (id);
        }break;
        case 3:{ //文件输入
			char filein[256] = {0};
			//fflush(stdin);
			printf("请输入文件名 ");
			scanf("%s", filein);
			FILE *input = fopen(filein, "r");
			if (input == NULL) {
				perror(filein);
				return -1;
			}
			printf("请选择插入顺序 ");
			scanf("%d", &func1);
			func1--;
			do {
				fscanf(input, "%d %d", &id, &score);
				if (id != 0) {
					(*Insert[func1])(this, NodeData(id, score));
				}
			} while (id);
			fclose(input);
		}break;
    }
    return 0;
}

int InsertNode(StuInfoSys* this, int func1)
{  //插入记录
    int id, score;
    switch (func1) {
        case 1:{   //指定位置
            int pos;
		    printf("请依次输入学号、成绩和要插入的位置\n");
            scanf("%d %d %d", &id, &score, &pos);
            if (pos<=0 || PosInsert(this, pos, NodeData(id, score))){
			    printf("bad position\n");
			    return -1;
            }
        }break;
        case 2:{  //有序链表
	 	    printf("请依次输入学号和成绩\n");
	 	    scanf("%d %d", &id, &score);
		    AscendingInsert(this, NodeData(id, score));
		    printf("\tmake node success\n");
        }break;
    }
    return 0;
}

int DeleteNode(StuInfoSys* this, int func1)
{  //删除记录
    int id;
    switch (func1) {
        case 1:{  //指定位置
            int pos;
	 	    printf("请输入位置\n");
            scanf("%d", &pos);
			if (pos <= 0 || PosDelete(this, pos)) {
				printf("bad position\n");
				return -1;
			}
	    }break;
        case 2:{ //指定学号
 	 	    printf("请输入学号\n");
 	 	    scanf("%d", &id);
			if (DataDelete(this, NodeData(id, 0))) {
				printf("no this id\n");
				return -1;
			}
	    }break;
    }
    return 0;
}

int FindNode(StuInfoSys* this)
{  //查找记录
     int id;
     printf("请输入要查找的学号\n");
     scanf("%d", &id);
     LNode* p = DataSearch(this, NodeData(id, 0));
     if (p)
         print_data(&p->next->data);
     else
         printf("no this id\n");
     return 0;
}

int Statistic(StuInfoSys* this)
{
    assert (this->list_ptr_);
    ListPtr p = this->list_ptr_;
    int tot_people = 0;
    int tot_score = 0;
    int max_score = 0;
    int tot_failed = 0;
    static int pass_line = 60;
	printf("请输入及格分数线 ");
	scanf("%d", &pass_line);
    while (p->next){
        p = p->next;
        tot_people++;
        tot_score += p->data.score;
        if (p->data.score > max_score)
            max_score = p->data.score;
        if (p->data.score < pass_line)
            tot_failed++;
    }
    printf("\t总人数 = %d \n", tot_people);
    printf("\t平均分 = %.2f \n", (float)tot_score / tot_people);
    printf("\t最高分 = %d \n", max_score);
    printf("\t不及格人数 = %d \n", tot_failed);
    return 0;
}

int Exist(StuInfoSys* this)
{
	return !empty(this);
}

int print_data(struct NodeData* data)
{
	printf("%d %d\n", data->id, data->score);
    return 0;
}

int print_list(StuInfoSys* this)
{
	assert(this->list_ptr_);
	LNode* p = this->list_ptr_;
	while (p->next) {
		NEXT(p);
		print_data(&p->data);
	}
	return 0;
}

int Write2File(StuInfoSys* this, int func1)
{
	char fileout[256] = { 0 };
	const char* open_mode[] = { "w", "a", "w" };
	printf("请输入文件名 ");
	scanf("%s", fileout);
	FILE *output = fopen(fileout, open_mode[func1-1]);
	if (output == NULL) {
		perror(fileout);
		return -1;
	}

	switch (func1) {
	case 1:   //重写学生文件
	case 2: {  //追加学生文件
		LNode* p = this->list_ptr_;
		while (p->next) {
			NEXT(p);
			fprintf(output, "%d %d\n", p->data.id, p->data.score);
		}
	}break;
	case 3: { //清空学生文件
		;// nothing to do
	}break;
    }

	fclose(output);
	return 0;
}

