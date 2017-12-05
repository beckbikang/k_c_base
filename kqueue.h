//
//  kqueue.h
//  mylib
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__kqueue__
#define __mylib__kqueue__

#include <stdio.h>

#include "klist.h"

typedef  LinkList* KQUEUE;

#define queue_new() link_new()

#define queue_enter(L,N) link_add_last(L, N)

#define queue_denter(L) link_remove_first(L)

#define queue_peek_header(L) LINK_HEAD(L)
#define queue_peek_tail(L) LINK_TAIL(L)

#define queue_free(L,Func) link_free(L, Func)

#define queue_size(L) LINK_SIZE(L)

#endif /* defined(__mylib__kqueue__) */
