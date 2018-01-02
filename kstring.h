//
//  kstring.h
//  mylib
//
//  Created by bikang on 18/1/2.
//  Copyright (c) 2018年 bikang. All rights reserved.
//

#ifndef __mylib__kstring__
#define __mylib__kstring__


#include <stdio.h>
#include <string.h>
#include "kheader.h"


#define DEFAULT_BUF_LEN 8//默认的长度
#define DEFAULT_BUF_STEP 2//增长指数

//字符串的定义
typedef struct _kstr{
    cstr str;
    kuint len;
}kstr;

//基本的函数的定义
kstr * kstr_create(cstr);
void kstr_free(kstr **);


//含有buffer的字符串的定义
typedef struct _kbufstr{
    cstr str;
    kuint opa;
    kuint len;
}kbufstr;

#define kbufstr_size(kbs) (kbs)->size
#define kbufstr_opa(kbs) (kbs)->opa
#define kbufstr_empty(kbs) (kbs)->size == 0


//创建多大的容量
kbufstr* kbufstr_create_opa(int);
//根据字符串创建
kbufstr* kbufstr_create_str(cstr);

//创建默认大小的
#define kbufstr_create kbufstr_create_opa(DEFAULT_BUF_LEN);
//释放
void kbufstr_free(kbufstr**);





#endif /* defined(__mylib__kstring__) */
