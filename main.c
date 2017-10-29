//
//  main.c
//  mylib
//
//  Created by bikang on 17/10/25.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include <stdio.h>
#include "klog.h"
//测试使用
void test_base();

int main(int argc, const char * argv[]) {
    //test_base();
    test_it();
    return 0;
}


void test_base(){
    int i = 1;
    printf("a start = %d",i);
}