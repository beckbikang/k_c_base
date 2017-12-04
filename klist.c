//
//  klist.c
//  mylib
//
//  Created by bikang on 17/12/1.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "klist.h"

//初始化list
static int init_link(LinkList*);
//创建一个节点
static LinkNode* init_node(void*);

static LinkNode* getNodeByCompare(LinkList *, link_compare_func,void*);

LinkList* link_new(){
    
    LinkList *link = (LinkList*)malloc(sizeof(LinkList));
    if (link == NULL) {
        puts("malloc link error");
        exit(-1);
    }
    init_link(link);
    
    return link;
}

static LinkNode* init_node(void *value){
    LinkNode* node = Node_New();
    if(node == NULL){
        puts("malloc LinkNode error");
        exit(-1);
    }
    Node_Init(node,value);
    return node;
}

int init_link(LinkList *link){
    link->size = 0;
    link->head = init_node(NULL);
    link->tail = init_node(NULL);
    return 0;
}

int link_free(LinkList ** link,link_call_back_func f){
    
    if (link == NULL) return 0;
    if(*link != NULL){
        link_destroy(*link, f);
        free(*link);
    }
    
    return 0;
}

void link_node_free(LinkNode *node,link_call_back_func func){
    if (node == NULL) return;
    
    if (func != NULL) {
        func(node->value);
    }
    free(node);
}


int link_destroy(LinkList *link,link_call_back_func free_func){
    LinkNode *node;
    if (link != NULL) {
        for (node=link->head; node!=link->tail; node = node->next) {
            if (free_func != NULL) {
                free_func(node->value);
            }
            free(node);
        }
        free(link->head);
        link->head = NULL;
        
        free(link->tail);
        link->tail = NULL;
    }
    return 0;
}


//在链表的尾部添加数据
int link_add_first(LinkList *link, void *value){
    if (link == NULL) return -1;
    
    LinkNode*node =  init_node(value);
    
    if (link->size == 0) {
        link->head = link->tail =node;
    }else{
        node->next = link->head;
        link->head->prev = node;
        link->head = node;
    }
    link->size++;
    return 0;
}
//在链表的头部添加数据
int link_add_last(LinkList *link, void *value){
    if (link == NULL) return -1;
    
    LinkNode*node =  init_node(value);
    
    if (link->size == 0) {
        link->head = link->tail =node;
    }else{
        link->tail->next = node;
        node->prev = node;
        link->tail = node;
    }
    link->size++;
    return 0;
}

//获取指定索引的节点
static LinkNode* getNode(LinkList *link,uint index){
    int i=1;
    LinkNode *node = NULL;
    if (index > link->size) return NULL;
    
    //出于效率考虑是从前查找还是从后查找
    if (index > (link->size)/2) {
        node=link->tail;
        for (i=link->size; i > index; i--) {
            node = node->prev;
        }
    }else{
        for (node = link->head; i<=index; i++) {
            node = node->next;
        }
    }
    return node;
}

//在index前插入
void *link_insert(LinkList *link,uint index,void*value){
    
    if (link == NULL)return NULL;
    
    LinkNode* index_node = getNode(link, index);
    if (index_node == NULL) return NULL;
    
    LinkNode*node =  init_node(value);
    
    if (index_node == link->head) {
        node->next = link->head;
        link->head->prev = node;
        link->head = node;
    }else{
        index_node->prev->next = node;
        node->prev = index_node->prev;
        node->next = index_node;
        index_node->prev = node;
    }
    
    link->size++;
    return node;
}
//删除指定节点的数据
void *link_remove(LinkList *link,uint index){
    
    LinkNode* index_node = getNode(link, index);
    if (index_node == NULL) return NULL;
    
    if (index_node == link->head) {
        link->head = link->head->next;
        link->head->prev = NULL;
        index_node->next = NULL;
    }else if(index_node == link->tail){
        link->tail->prev->next = NULL;
        index_node->prev = NULL;
    }else{
        index_node->next->prev = index_node->prev;
        index_node->prev->next = index_node->next;
    }
    link->size--;
    return index_node;
}

//头部删除
void *link_remove_first(LinkList *link){
    if (link->size == 0) {
        return NULL;
    }
    LinkNode *node;
    node = link->head;
    link->head = link->head->next;
    link->head->prev = NULL;
    
    node->prev = NULL;
    node->next = NULL;
    
    link->size--;
    return node;
}
//尾部删除
void *link_remove_last(LinkList *link){
    if (link->size == 0) {
        return NULL;
    }
    LinkNode *node;
    node = link->tail;
    link->tail = link->tail->prev;
    link->tail = NULL;
    
    node->prev = NULL;
    node->next = NULL;
    
    link->size--;
    return node;
}

//获取某一个节点的值
void *link_get(LinkList *link,uint index){
    LinkNode* index_node = getNode(link, index);
    if (index_node == NULL) return NULL;
    return index_node;
}
//设置某一个节点的值
void *link_set(LinkList *link,uint index, void* value){
    LinkNode* index_node = getNode(link, index);
    if (index_node == NULL) return NULL;
    
    index_node->value = value;
    
    return index_node;
}

static LinkNode* getNodeByCompare(LinkList *link, link_compare_func func,void*value){
    LinkNode* node = NULL;
    int i = 1;
    
    for (node = link->head; i<link->size; i++) {
        if (func((void*)node,value) != 0) {
            break;
        }
        node = node->next;
    }
    return node;
}

//按照条件搜索
void *link_remove_obj(LinkList *link, void*value, link_compare_func func){
    LinkNode *index_node = getNodeByCompare(link,func,value);
    if(index_node == NULL){
        return NULL;
    }
    if (index_node == link->head) {
        link->head = link->head->next;
        link->head->prev = NULL;
        index_node->next = NULL;
    }else if(index_node == link->tail){
        link->tail->prev->next = NULL;
        index_node->prev = NULL;
    }else{
        index_node->next->prev = index_node->prev;
        index_node->prev->next = index_node->next;
    }
    link->size--;
    return index_node;
}

//设置链表对象
void *link_set_obj(LinkList *link, void *value,void *new_value, link_compare_func func){
    
    LinkNode *index_node = getNodeByCompare(link,func,value);
    if(index_node == NULL){
        return NULL;
    }
    index_node->value = new_value;

    return index_node;
}



void printLink(LinkList* link){
    int i;
    LinkNode *node = link->head;
    puts("#######start print####");
    for (i=0; i<link->size; i++) {
        printf("%p\n",node);
        node = node->next;
    }
    puts("#######end print####");
}





