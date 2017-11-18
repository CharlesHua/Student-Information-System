/***************************************************
Copyright (C) 2017 Charles Hua. All rights reserved.
Last edited date: 2017.11.17
project name: StudentInfoSys
file name: stu_info_sys.c

ѧ����Ϣϵͳ
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
        case 0:   //ͷ�巨
        case 1:   //β�巨
        case 2:{ //ѧ������
		    printf("��������������ѧ�źͳɼ�,��ѧ��0����\n");
            do{
                scanf("%d %d", &id, &score);
                if (id != 0){
                    (*Insert[func1])(this, NodeData(id, score));
	    			printf("\tmake node success\n");
                }
            }while (id);
        }break;
        case 3:{ //�ļ�����
			char filein[256] = {0};
			//fflush(stdin);
			printf("�������ļ��� ");
			scanf("%s", filein);
			FILE *input = fopen(filein, "r");
			if (input == NULL) {
				perror(filein);
				return -1;
			}
			printf("��ѡ�����˳�� ");
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
{  //�����¼
    int id, score;
    switch (func1) {
        case 1:{   //ָ��λ��
            int pos;
		    printf("����������ѧ�š��ɼ���Ҫ�����λ��\n");
            scanf("%d %d %d", &id, &score, &pos);
            if (pos<=0 || PosInsert(this, pos, NodeData(id, score))){
			    printf("bad position\n");
			    return -1;
            }
        }break;
        case 2:{  //��������
	 	    printf("����������ѧ�źͳɼ�\n");
	 	    scanf("%d %d", &id, &score);
		    AscendingInsert(this, NodeData(id, score));
		    printf("\tmake node success\n");
        }break;
    }
    return 0;
}

int DeleteNode(StuInfoSys* this, int func1)
{  //ɾ����¼
    int id;
    switch (func1) {
        case 1:{  //ָ��λ��
            int pos;
	 	    printf("������λ��\n");
            scanf("%d", &pos);
			if (pos <= 0 || PosDelete(this, pos)) {
				printf("bad position\n");
				return -1;
			}
	    }break;
        case 2:{ //ָ��ѧ��
 	 	    printf("������ѧ��\n");
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
{  //���Ҽ�¼
     int id;
     printf("������Ҫ���ҵ�ѧ��\n");
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
	printf("�����뼰������� ");
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
    printf("\t������ = %d \n", tot_people);
    printf("\tƽ���� = %.2f \n", (float)tot_score / tot_people);
    printf("\t��߷� = %d \n", max_score);
    printf("\t���������� = %d \n", tot_failed);
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
	printf("�������ļ��� ");
	scanf("%s", fileout);
	FILE *output = fopen(fileout, open_mode[func1-1]);
	if (output == NULL) {
		perror(fileout);
		return -1;
	}

	switch (func1) {
	case 1:   //��дѧ���ļ�
	case 2: {  //׷��ѧ���ļ�
		LNode* p = this->list_ptr_;
		while (p->next) {
			NEXT(p);
			fprintf(output, "%d %d\n", p->data.id, p->data.score);
		}
	}break;
	case 3: { //���ѧ���ļ�
		;// nothing to do
	}break;
    }

	fclose(output);
	return 0;
}

