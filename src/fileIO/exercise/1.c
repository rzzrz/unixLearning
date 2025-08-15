/**
 * @file 1.c
 * @author rzzrz    
 * @brief   创建一个新文件 output.txt
            写入字符串 "Hello, Unix I/O!"
            使用 O_CREAT | O_WRONLY 标志，权限设置为 0644
            检查所有系统调用的错误返回值
 * @version 0.1
 * @date 2025-08-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>



int main(){

    int fd = open("output.txt",O_CREAT | O_WRONLY, 0644);
    if(fd == -1){
        perror("open faild");
        return -1;
    }

    char * msg = "Hello, Unix I/O!";
    ssize_t s = write(fd,msg,strlen(msg));

    if(s == -1){
        perror("write faild");
        close(fd);
        return -1;
    }
    

    return 0;
}