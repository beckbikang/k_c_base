//
//  avector.h
//  mylib
//
//  Created by bikang on 17/11/27.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__avector__
#define __mylib__avector__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//每次增加三倍的空间
#define Avector_add_step 3

typedef struct avector{
    void **__store;
    int _size;
    int _cap;
}Avector;

//整体分配空间
#define NewAvector() (Avector*)malloc(sizeof(Avector));
//创建
#define Avector(Av,Cap)\
{\
    Av->_cap = Cap;Av->_size = 0;\
    Av->__store = (void**)calloc(Cap,sizeof(void*));\
}
//增加数据
#define Avector_Append(Av,V)\
{\
    if(Av->_cap == Av->_size) _Avector_Extend(Av);\
    Av->__store[Av->_size++] = V;\
}
//扩展数据
#define _Avector_Extend(Av)\
{\
    int _cap = Avector_add_step * Av->_size;\
    Av->__store = (void**)realloc(Av->__store,sizeof(void**)*_cap);\
    Av->_cap =_cap;\
}
//是否空间
#define Av_Free(Av)\
{\
    free(Av->__store);\
}
//摧毁数据
#define Av_Destroy(Av)\
{\
free(Av);\
}

//设置变量
#define Avector_Get(Av,I) (Av->__store[I])
#define Avector_Set(Av,I,V)(Av->__store[I] = V;)


#endif /* defined(__mylib__avector__) */
