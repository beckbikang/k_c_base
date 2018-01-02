//
//  ksort.c
//  mylib
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "ksort.h"

//直接使用指针实现
void k_subinsert_sort(void *a,uint size,link_compare_func comp,uint start,uint end){
    
    char *tmp = (char*)malloc(size);
    char *ptr = (char*)a;
    char *p;
    if (tmp == NULL) return;
    
    register int i,j;
    
    //从第start个元素开始
    for (i = start+1; i <= end; i++) {
        //设置临时变量
        memcpy(tmp, ptr+i*size, size);
        //设置哨兵
        j = i;
        // 比较当前值和下一个值的比较
        //如果tmp < ptr+(j-1)*size;
        while (j > start && comp(tmp,(p=ptr+(j-1)*size))) {
            memcpy(p+size, p, size);
            j--;
        }
        //j < i才有意义哦
        if (j < i) {
            memcpy(ptr+j*size, tmp, size);
        }
    }
    free(tmp);
}


