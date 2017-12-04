//
//  klog.c
//  mylib
//
//  Created by bikang on 17/10/27.
//  Copyright (c) 2017年 bikang. All rights reserved.
//

#include "klog.h"

//定义基本的结构
typedef struct Klog{
    const char* logpath;//存储地址
    int fd;//文件句柄
    ULONG flag;//日志发送的地方
    char splite_char[5];//分隔符
    short is_show_line;//是否显示行+文件名,默认不显示
    
}KLogger;


//初始化一个数据
static KLogger KL = {"",-1,LOG_DEBUG,PUT_STD_OUT};

//根据条件初始化日志
int logInit(const char *str_path,ULONG flag){
    if (str_path == NULL){
        return KLOG_FAILD;
    }
    KL.flag = flag;
    KL.logpath = str_path;
    if((flag & PUT_SFILE) == PUT_SFILE){
        KL.fd = open(str_path, O_WRONLY|O_CREAT|O_APPEND,S_IRWXU|S_IRWXO);
        if(KL.fd < 0){
            return KLOG_FAILD;
        }
    }
    if ((KL.flag & PUT_SYSLOG) == PUT_SYSLOG) {
        //记录pid 立即打开连接， 记录用户日志
        openlog(KL.logpath, LOG_PID | LOG_NDELAY, LOG_USER);
    }
    int len = LOG_DEFAULT_SPLITE_LEN;
    memset(KL.splite_char, '\0', len);
    KL.splite_char[0] = LOG_DEFAULT_SPLITE;
    KL.is_show_line = 0;
    return KLOG_SUCESS;
}


//重新设置路径
int setLogerPath(const char *str_path){
    logClose();
    if (str_path && strlen(str_path) > 0){
        return logInit(str_path,KL.flag);
    }
    return KLOG_FAILD;
}
//设置保存的类型
void setLogerSaveType(ULONG flag){
    KL.flag = flag;
}
//添加一个种类型
void addLogerSaveType(ULONG flag){
     KL.flag = KL.flag| flag;
}
//移除一种类型
void removeLogerSaveType(ULONG flag){
    KL.flag = KL.flag & ~flag;
}
//获取flag
ULONG getLogerFlag(){
    return KL.flag;
}

//设置切分符号
void setSpliteData(const char *split){
    int len = LOG_DEFAULT_SPLITE_LEN;
    if(strlen(split)> 0 && strlen(split) < len){
        strcpy(KL.splite_char, split);
    }
}
//设置是否显示文件信息
void setShowFile(int is_show){
    KL.is_show_line = is_show;
}


int logClose(){
    
    if(KL.fd != -1 && close(KL.fd) < 0){
        //todo  add something
        return KLOG_FAILD;
    }
    
    if ((KL.flag & PUT_SYSLOG) == PUT_SYSLOG) {
        closelog();
    }
    KL.fd = -1;
    
    return KLOG_SUCESS;
}

//获取当前时间
char *getCurrentTime(){
    struct tm *ptr;
    int len = SHOW_TIME_LEN;
    time_t tl;
    char *buf = (char*)malloc(sizeof(char) * len);
    
    tl = time(NULL);
    ptr = localtime(&tl);
    buf[strftime(buf, len , "%Y-%m-%d %H:%M:%S", ptr)]='\0';
    return buf;
}

/**
处理日志:
    1 输出时间，文件名，行数，你需要的信息
    2 注意各个数据的切分
    3 注意数据的长度
 
 **/
void klogMesg(int level, char *file,int line,const char *fmt, ...){
    char str_format[MAX_LOG_LEN];
    char buffer[MAX_LOG_LEN];
    va_list args;
    
    memset(str_format, '\0', MAX_LOG_LEN);
    memset(buffer, '\0', MAX_LOG_LEN);
    char *atime = getCurrentTime();
    
    //获取当前的需要格式化的字符串
    if (KL.is_show_line == 1){
        snprintf(str_format, MAX_LOG_LEN,"%s%s%s:%d%s%s%s%s",
        KLONG_NAME[level],KL.splite_char,file,line,KL.splite_char,
                 atime,KL.splite_char,fmt);
    }else{
        snprintf(str_format, MAX_LOG_LEN,"%s%s%s%s%s\n",
                 KLONG_NAME[level],KL.splite_char,
                 atime,KL.splite_char,fmt);
    }
    //获取需要拼接的字符串
    
    va_start(args,fmt);
    size_t buf_len = vsnprintf(buffer,MAX_LOG_LEN, str_format,args);
    va_end(args);
    //拼接出需要的字符串，然后根据flag输出到对应的fd里面
    
    if ((KL.flag & PUT_STD_OUT) == PUT_STD_OUT) {
        printf("%s",buffer);
        fflush(stdout);
    }
    if ((KL.flag & PUT_STD_ERR) == PUT_STD_ERR) {
        printf("%s",buffer);
        fflush(stderr);
    }
    
    
    if ((KL.flag & PUT_SYSLOG) == PUT_SYSLOG) {
        syslog(level, buffer,"");
    }
    
    if ((KL.flag & PUT_SFILE) == PUT_SFILE) {
        write(KL.fd, buffer, buf_len);
    }
    free(atime);
}



void test_log(){
    printf("test it\n");
    int ret;
    
    //打开日志
    ret = logInit("/Users/kang/Documents/CppProject/xcode/mylib/mylib/t.log",PUT_STD_OUT | PUT_SFILE);//| PUT_SYSLOG);
    if (ret < 0) {
        puts("\nopen log error\n");
    }else{
        puts("open log sucess\n");
    }
    //打印当前时间
    char *ptime;
    ptime = getCurrentTime();
    printf("%s;len=%ld\n",ptime,strlen(ptime));
    
    //打印级别
    printf("kl.flag=%x\n",(int)getLogerFlag());
    
    //写日志
    klogTrace("%s","atest");
    klogDebug("%s","atest");
    klogInfo("%s","atest");
    klogWarning("%s","atest");
    klogError("%s","atest");
    klogFatal("%s","atest");
    
    //写日志
    setShowFile(1);
    setSpliteData("||");
    klogTrace("%s","atest");
    
    
    ret = logClose();
    if (ret < 0) {
        puts("close log error\n");
    }else{
        puts("close log sucess\n");
    }
}

