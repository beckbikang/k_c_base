//
//  ksort.h
//  mylib
//
//  Created by bikang on 17/12/5.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__ksort__
#define __mylib__ksort__


#include "kheader.h"

void k_subinsert_sort(void *,uint,link_compare_func,uint,uint);

#define k_insert_sort(a,len,size,func)\
k_subinsert_sort(a,size,func,0,len-1)



#endif /* defined(__mylib__ksort__) */
