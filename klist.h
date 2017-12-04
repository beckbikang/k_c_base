//
//  klist.h
//  mylib
//
//  Created by bikang on 17/12/1.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__klist__
#define __mylib__klist__

#include <stdio.h>
#include <stdlib.h>

//比较函数
typedef int ( * link_compare_func ) ( void *, void * );
//回调函数
typedef void ( *link_call_back_func ) ( void * );

typedef struct _LinkNode {
    void *value;
    struct _LinkNode *prev;
    struct _LinkNode *next;
}LinkNode;

typedef struct _LinkList{
    uint size;
    LinkNode *tail;
    LinkNode *head;
}LinkList;

//是否节点

void link_node_free(LinkNode *,link_call_back_func);

//创建和释放
LinkList* link_new();
int link_free(LinkList **,link_call_back_func);
//初始化
int link_init(LinkList *);
//销毁
int link_destroy(LinkList *,link_call_back_func);

//前后添加数据
int link_add_first(LinkList *, void *);
int link_add_last(LinkList *, void *);

//特殊位置查找和删除
void *link_insert(LinkList *,uint,void*);
//删除
void *link_remove(LinkList *,uint);

//删除头和尾
void *link_remove_first(LinkList *);
void *link_remove_last(LinkList *);

//设置对象
void *link_remove_obj(LinkList *, void*, link_compare_func);
void *link_set_obj(LinkList *, void*,void*, link_compare_func);

//设置数据
void *link_get(LinkList *,uint);
void *link_set(LinkList *,uint, void*);


void printLink(LinkList*);



#define Node_New() (LinkNode*)malloc(sizeof(LinkNode));

#define Node_Init(NODE,DATA)\
NODE->value=DATA;\
NODE->prev=NULL;\
NODE->next=NULL;\

#define LINK_TAIL(L) (L)->tail
#define LINK_HEAD(L) (L)->head
#define LINK_SIZE(L) (L)->size













#endif /* defined(__mylib__klist__) */
