//
//  klog.h
//  mylib
//
//  Created by bikang on 17/10/27.
//  Copyright (c) 2017年 bikang. All rights reserved.
// not thread safe

#ifndef __mylib__klog__
#define __mylib__klog__

#ifdef __cplusplus
extern "C" {
#endif


    
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <syslog.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


//定义unsigned long长度
typedef unsigned long ULONG;

//默认的切分字符串长度
#define LOG_DEFAULT_SPLITE '`'
#define LOG_DEFAULT_SPLITE_LEN 5;
    
//时间的长度
#define SHOW_TIME_LEN  64;
    
//最长的路径
#define MAX_LOG_LEN 4096
    
//正确和错误
#define KLOG_FAILD -1
#define KLOG_SUCESS 0

//日志的级别
typedef enum {
    KLOG_TRACE = 0,
    KLOG_DEBUG,
    KLOG_INFO,
    KLOG_WARING,
    KLOG_ERROR,
    KLOG_FATAL,
}KLOG_LEVEL;

static const char *KLONG_NAME[] = {
    "[trace]", "[debug]", "[info]", "[warning]", "[error]", "[fatal]"
};
    
//日志存储的地方
typedef enum {
    PUT_STD_OUT = 1<< 0,
    PUT_STD_ERR = 1 << 1,
    PUT_SFILE = 1 << 2,
    PUT_SYSLOG = 1 << 3,
}SAVE_TYPE;

//初始化和关闭
int logInit(const char *str_path,ULONG type);
int logClose();
    
//设置各种数据
int setLogerPath(const char *str_path);
ULONG getLogerFlag();
void setLogerSaveType(ULONG flag);
void addLogerSaveType(ULONG flag);
void removeLogerSaveType(ULONG flag);
//设置切分符号
void setSpliteData(const char *split);
//设置是否显示文件信息
void setShowFile(int is_show);
    
//获取路径
const char* getLogPath();

void klogMesg(int level, char *file,int line,const char *fmt, ...);
//可以显示
#define klogTrace(...) klogMesg(KLOG_TRACE,__FILE__,__LINE__,__VA_ARGS__);
#define klogDebug(...) klogMesg(KLOG_DEBUG,__FILE__,__LINE__,__VA_ARGS__);
#define klogInfo(...) klogMesg(KLOG_INFO,__FILE__,__LINE__,__VA_ARGS__);
#define klogWarning(...) klogMesg(KLOG_WARING,__FILE__,__LINE__,__VA_ARGS__);
#define klogError(...) klogMesg(KLOG_ERROR,__FILE__,__LINE__,__VA_ARGS__);
#define klogFatal(...) klogMesg(KLOG_FATAL,__FILE__,__LINE__,__VA_ARGS__);

void test_log();


#ifdef __cplusplus
}
#endif

#endif /* defined(__mylib__klog__) */
