//
//  kavl_tree.h
//  mylib
//
//  Created by bikang on 17/11/23.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#ifndef __mylib__kavl_tree__
#define __mylib__kavl_tree__

#ifdef __cplusplus
extern "C" {
#endif
    
#include <stdio.h>
#include <stdlib.h>
    
#define AvlTreeDataType int

//定义一颗树的基本结构
typedef struct _avlNode{
    struct _avlNode *right;
    struct _avlNode *left;
    unsigned int height;
    AvlTreeDataType data;
}avlNode;
    
    
#ifdef __cplusplus
}
#endif
#endif /* defined(__mylib__kavl_tree__) */
