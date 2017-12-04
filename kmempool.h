//
//  kmempool.h
//  mylib
//  简单的内存池
//  Created by bikang on 17/11/22.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__kmempool__
#define __mylib__kmempool__

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>

#define KM_ADD_MEM_STEP 3 //每次增加两倍的空间
#define KM_PART_MEM 96 //每次分配的空间大小
#define KM_ONE_M 1048576 //1M占用多少字节

    
    
//基础的管理链表的结构
typedef struct _kblock{
    struct _kblock *pre;
    struct _kblock *next;
    char *pdata;
}kblock;

//基础的数据空间
typedef struct _kmempool{
    
    unsigned int block_size;//每个block的大小
    unsigned int block_count;//block的数量
    unsigned int add_step;
    unsigned int used_count;//使用的数量
    unsigned int free_count;//剩余的数量

    kblock *used_head;//使用的头
    kblock *used_tail;//使用的尾部

    kblock *free_head;//剩余头
    kblock *free_tail;//剩余尾
    
    
    char *pkblock;//存储基本信息
    char *pmem; //存储数据
}kmempool;

//初始化内存池
kmempool* kmempool_init(unsigned int block_size, unsigned int block_count);

//内存池分配内存
void* kmempool_malloc(kmempool* km,unsigned int size);

//内存池释放内存
int kmempool_free(kmempool* km, void *ptr);
    
//摧毁内存池
int kmempool_destry(kmempool* km);


    
#ifdef __cplusplus
}
#endif


#endif /* defined(__mylib__kmempool__) */
