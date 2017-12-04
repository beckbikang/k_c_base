//
//  kdaemon.c
//  mylib
//
//  Created by bikang on 17/10/29.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "kdaemon.h"

/**
 
 **/
int daemon_it(){
    
    pid_t pid,sid;
    //创建一个子进程
    pid = fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }
    if (pid > 0){
        exit(EXIT_SUCCESS);
    }
    //设置文件掩码,最大权限
    umask(0);
    //创建一个新的会话id
    sid = setsid();
    if (sid < 0){
        exit(EXIT_FAILURE);
    }
    //处理信号
    //切换到根目录
    if (chdir("/") < 0) {
        exit(EXIT_FAILURE);
    }
    
    //关闭标准输出，输入，error
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
 
    return 0;
}

void test_daemon(){
    puts("test daemon");
    daemon_it();
    while (1) {
        puts("waiting...\n");
        sleep(1);
    }
}


