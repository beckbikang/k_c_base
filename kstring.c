//
//  kstring.c
//  mylib
//
//  Created by bikang on 18/1/2.
//  Copyright (c) 2018年 bikang. All rights reserved.
//

#include "kstring.h"


//基本的函数的定义
kstr * kstr_create(cstr str){
    //定义 str的基本长度
    kuint len;
    
    kstr * a_kstr = (kstr *)malloc(sizeof(kstr));
    if (a_kstr == NULL) {
        return NULL;
    }
    a_kstr->len = 0;
    if(str == NULL){
        a_kstr->str = NULL;
        return a_kstr;
    }
    
    //获取长度
    len = (kuint)strlen(str);
    a_kstr->str = malloc(sizeof(cstr)*len);
    if(a_kstr->str  == NULL){
        free(a_kstr);
        return NULL;
    }
    
    //字符串的基本处理
    a_kstr->len = len;
    memcpy(a_kstr->str, str, len);
    
    return a_kstr;
}

//释放空间
void kstr_free(kstr ** in_kstr){
    if(in_kstr == NULL) return;
    
    if (*in_kstr != NULL) {
        free((*in_kstr)->str);
        (*in_kstr)->str = NULL;
        free(*in_kstr);
        *in_kstr = NULL;
    }
}

//创建字符串
static cstr get_cstr(int opa){
    cstr str = (cstr) malloc(sizeof(cstr) *opa);
    if(str == NULL) return NULL;
    memset(str, 0x00, opa);
    return str;
}

//给字符串重新分配空间

static int resize_kbufstr(kbufstr * a_kbufstr, int new_size){
    kuint len;
    cstr str = get_cstr(new_size);
    if(str == NULL){
        return 0;
    }
    
    //拷贝数据到新的空间
    len = (new_size > a_kbufstr->len) ? (a_kbufstr->len):new_size;
    memcpy(str, a_kbufstr->str, len);
    
    free(a_kbufstr->str);
    a_kbufstr->opa = new_size;
    a_kbufstr->str = str;
    
    return 1;
}

//创建多大的容量
kbufstr* kbufstr_create_opa(int opa){

    if(opa <= 0){
        opa = DEFAULT_BUF_LEN;
    }
    //分配空间
    kbufstr * a_kbufstr = (kbufstr *)malloc(sizeof(kbufstr));
    if(a_kbufstr == NULL) return NULL;
    
    a_kbufstr->str = (cstr)get_cstr(opa);
    if(a_kbufstr->str == NULL){
        free(a_kbufstr);
        return NULL;
    }
    
    a_kbufstr->opa = opa;
    a_kbufstr->len = 0;
    return a_kbufstr;
}



//根据字符串创建
kbufstr* kbufstr_create_str(cstr str){
    kuint len,total_size;
    //分配空间
    kbufstr * a_kbufstr = (kbufstr *)malloc(sizeof(kbufstr));
    if(a_kbufstr == NULL) return NULL;
    
    len = (kuint) strlen(str);
    total_size = len + DEFAULT_BUF_LEN;
    
    //释放空间
    a_kbufstr->str = get_cstr(total_size);
    if (a_kbufstr->str == NULL) {
        free(a_kbufstr);
        return NULL;
    }
    
    //设置长度，拷贝内容
    a_kbufstr->opa = total_size;
    a_kbufstr->len = len;
    memcpy(a_kbufstr->str, str, len);
    
    return a_kbufstr;
}

//释放
void kbufstr_free(kbufstr** ak){
    if (ak == NULL) return;
    if (*ak != NULL){
        
        free((*ak)->str);
        (*ak)->str = NULL;
        free(*ak);
        *ak = NULL;
    }
}









