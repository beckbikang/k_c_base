//
//  kmempool.c
//  mylib
//
//  Created by bikang on 17/11/22.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "kmempool.h"

//真正的分配内存函数
int static   kmempool_create(kmempool* km, int block_size, unsigned int block_count);

//初始化内存池
kmempool* kmempool_init(unsigned int block_size, unsigned int block_count){
    kmempool *km = (kmempool *)malloc(sizeof(kmempool));
    if (km == NULL) return NULL;
    
    km->block_count = block_count;
    km->block_size = block_size;
    km->add_step = KM_ADD_MEM_STEP;
    km->free_head = NULL;
    km->free_tail = NULL;
    km->used_tail = NULL;
    km->used_head = NULL;
    km->used_count = 0;
    km->free_count = block_count;
    
    kmempool_create(km,block_size,block_count);
    
    return km;
}
//真正的内存分配代码
static int kmempool_create(kmempool* km, int block_size, unsigned int block_count){
    kblock *pos = NULL;
    unsigned int i;
    
    km->pkblock = (char*)malloc(sizeof(kblock)*block_count);
    km->pmem = (char*)malloc((block_size +sizeof(kblock*))*block_count);
    
    for (i=0; i<block_count; i++) {
        pos = (kblock*)(km->pkblock+(sizeof(kblock)*i));
        pos->pdata = km->pmem+(block_size +sizeof(kblock*))*i;
        pos->next = NULL;
        pos->pre = km->free_tail;
        
        if(km->free_head == NULL){
            km->free_head = km->free_tail = pos;
        }else{
            km->free_tail->next = pos;
            km->free_tail = pos;
        }
    }
    
    return 0;
}

//内存池分配内存.  从一个队列移除，进入另外一个队列
void* kmempool_malloc(kmempool* km,unsigned int size){
    kblock *pos = NULL;
    
    if(km->free_head  == NULL){
        kmempool_create(km,km->add_step*km->block_count,km->block_size);
    }
    
    pos = km->free_head;
    
    km->free_head = km->free_head->next;
    km->free_head->pre = NULL;
    
    pos->next = NULL;
    
    km->free_count --;
    km->used_count ++;
    
    if(km->used_tail == NULL){
        pos->pre =  NULL;
    }else{
       pos->pre = km->used_tail;
    }
    
    
    if (km->used_head == NULL) {
        km->used_head = km->used_tail = pos;
    }else {
        km->used_tail->next = pos;
        km->used_tail = pos;
    }
    //留下data里一个指针的空间，用于保存与数据关联的块地址
    pos->pdata = (char*)pos;
    
    return (char*)(pos->pdata)+sizeof(kblock*);
}


//内存池释放内存
int kmempool_free(kmempool* km, void *ptr){
    
    char *realMem = (char*)ptr - sizeof(kblock*);
    kblock *pos = (kblock *)realMem;
    
    //printf("%p=%p",km->used_head,pos);
  
    if (pos == NULL) {
        return -1;
    }
    //从已使用里面摘除
    if(pos->pre == NULL){//是头
        km->used_head = (kblock *)(pos->next);
        if(km->used_head != NULL){
            km->used_head->pre = NULL;
        }
    }else if(pos->next == NULL){//尾部
        km->used_tail = pos->pre;
        if(km->used_tail != NULL){
            km->used_tail->next = NULL;
        }
    }else{//中间
        pos->pre->next = pos->next;
        pos->next->pre = pos->pre;
    }
    km->used_count--;
   
    //放入到未使用里面
    pos->pdata = (char*)realMem;
    pos->next = NULL;
    pos->pre  = km->free_tail;
    
    km->free_count++;
    if(km->free_head == NULL){
        km->free_head = km->free_tail = pos;
    }else{
        km->free_tail->next = pos;
        km->free_tail = pos;
    }
    
    return 0;
}


//摧毁内存池
int kmempool_destry(kmempool* km){
    if ((km != NULL) && (km->block_size > 0)){
        free(km->pkblock);
        free(km->pmem);
        km = NULL;
    }
    return 0;
}




