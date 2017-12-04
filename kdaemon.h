//
//  kdaemon.h
//  mylib
//
//  Created by bikang on 17/10/29.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__kdaemon__
#define __mylib__kdaemon__


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
    
int daemon_it();
    
void test_daemon();
    
#ifdef __cplusplus
}
#endif

#endif /* defined(__mylib__kdaemon__) */
