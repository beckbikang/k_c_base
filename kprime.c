//
//  kprime.c
//  mylib
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "kprime.h"

//下一个素数
int next_primer(int n){
    n++;
    if (n%2 == 0) {
        n++;
    }
    for(;!is_primer(n);n=n+2);
    
    return n;
}

//判断是否是素数
int is_primer(int n){
    
    int j;
    
    if (n == 2 || n == 3) {
        return 1;
    }
    
    if (n == 1 || n%2 == 0) {
        return 0;
    }
    
    for (j = 3; j*j < n; j++) {
        if(n/j == 0) return 0;
    }
    return 1;
}