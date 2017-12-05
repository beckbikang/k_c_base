//
//  kstack.h
//  mylib
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__kstack__
#define __mylib__kstack__

#include <stdio.h>
#include "klist.h"

typedef  LinkList* KSTACK;

#define stack_new() link_new()

#define stack_push(L,N) link_add_first(L, N)

#define stack_pop(L) link_remove_first(L)

#define stack_peek(L) LINK_HEAD(L)

#define stack_free(L,Func) link_free(L, Func)

#define stack_size(L) LINK_SIZE(L)

#endif /* defined(__mylib__kstack__) */
