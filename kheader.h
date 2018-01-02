//
//  kheader.h
//  mylib
//
//   预计后期整理所有的头文件统一放到这里
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef mylib_kheader_h
#define mylib_kheader_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//比较函数
typedef int ( * link_compare_func ) ( void *, void * );
//回调函数
typedef void ( *link_call_back_func ) ( void * );

//定义unsigned int
typedef  unsigned int kuint;
typedef unsigned long kulong;
//定义char*
typedef char *                      cstr;

#endif
