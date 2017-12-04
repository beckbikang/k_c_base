//
//  main.c
//  mylib
//
//  Created by bikang on 17/10/25.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "klog.h"
#include "kdaemon.h"
#include "kmempool.h"

#include "avector.h"

#include "klist.h"

struct data{
    int a;
};
int match_data ( void *d1, void *d2){
    struct data* dd1 = (struct data*)d1;
    struct data* dd2 = (struct data*)d2;
    if(dd1->a > dd2->a){
        return 1;
    }else if(dd1->a == dd1->a){
        return 0;
    }else{
        return -1;
    }
}

//测试使用
void test_base();//简单测试
void test_log2();//日志测试
void test_mempool();//内存池测试
void put_mempool();//测试内存池
void test_avector();//测试动态数组
void test_linklist();//测试链表
void printLink2(LinkList* link){
    int i;
    LinkNode *node = link->head;
    puts("#######start print####");
    for (i=0; i<link->size; i++) {
        if (node->value != NULL) {
            //printf("%p\n",node);
            printf("%p,%d\n",node,((struct data*)(node->value))->a);
        }
        node = node->next;
    }
    puts("#######end print####");
}


int main(int argc, const char * argv[]) {
    //test_base();
    //test_log();
    //test_daemon();
    //test_log2();
    //test_mempool();
    //test_avector();
    test_linklist();
    return 0;
}


//
void test_linklist(){
    puts("start linklist");
    LinkList* link = link_new();
    
    struct data d1;
    d1.a = 11;
    link_add_last(link, &d1);
    
    struct data d2;
    d2.a = 12;
    link_add_first(link, &d2);
    printLink(link);
    
    //insert
    struct data d3;
    d3.a = 13;
    link_insert(link, 1, &d3);
    printLink(link);
    
    //remove
    LinkNode *node = link_remove(link, 1);
    link_node_free(node,NULL);
    
    //insert
    struct data d4;
    d4.a = 14;
    link_insert(link, 1, &d4);
    printLink(link);
    
    //insert
    struct data d5;
    d5.a = 15;
    link_insert(link, 1, &d5);
    printLink(link);
    printLink2(link);
    
    //remove first
    node = link_remove_first(link);
    link_node_free(node,NULL);
    //remove last
    node = link_remove_last(link);
    link_node_free(node,NULL);
    
    //get node
    node = link_get(link, 0);
    printf("node=%d\n",((struct data*)(node->value))->a);
    node = link_get(link, 1);
    printf("node=%d\n",((struct data*)(node->value))->a);
    
    //set node data
    struct data d6;
    d6.a = 33;
    link_set(link, 0, &d6);
    printLink2(link);
    //search and find
    struct data d7;
    d7.a = 99;
    link_set_obj(link,&d6,&d7,match_data);
    link_insert(link, 1, &d6);
    printLink2(link);
    
    link_remove_obj(link, &d6, match_data);
    printLink2(link);
    
}

void test_avector(){
    printf("start test vector!\n");
    Avector *avl = NewAvector();
    Avector(avl, 1);
    char *str = "abc";
    Avector_Append(avl, str);
    char *str2 = "eee";
    Avector_Append(avl, str2);
    printf("size=%d,cap=%d\n",avl->_size,avl->_cap);
    printf("avl[0]=%s\n",Avector_Get(avl,0));
    printf("avl[1]=%s\n",Avector_Get(avl,0));
    Av_Free(avl);
    Av_Destroy(avl);
}

void test_mempool(){
    kmempool*km = kmempool_init(96, 10);
    put_mempool(km);
    char *ptr = kmempool_malloc(km, 30);
    char *qtr;
    printf("\n\n%d\n",sizeof(kblock*));
    qtr = ptr+sizeof(kblock*);
    strcpy(qtr, "abc");
    qtr[3] = '\0';
    printf("ptr=%s\n",qtr);
    
    kmempool_free(km, ptr);
    
    puts("after free\n");
    put_mempool(km);
    kmempool_destry(km);
}

void put_mempool(kmempool*km){
    kblock *pos;
    pos = km->free_head;
    while (pos != NULL) {
        printf("%p\n",pos);
        pos = pos->next;
    }
    
}


void test_log2(){
    logInit("/Users/kang/Documents/CProject/php-5.6.6/ext/new_ext/t.log", PUT_SFILE);
    klogTrace("%s","abc");
}

void test_base(){
    int i = 1;
    printf("a start = %d",i);
}