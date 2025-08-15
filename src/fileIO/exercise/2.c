/**
 * @file 2.c
 * @author rzzrz
 * @brief   打开题目 1 创建的 output.txt
            读取文件内容并打印到终端
            使用动态缓冲区（lseek 获取文件大小）
            处理读取错误和空文件情况
 * @version 0.1
 * @date 2025-08-13
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

int main(){
    int fd = open("./output.txt",O_RDONLY);
    if(fd == -1){
        perror("open faild");
        return -1;
    }

    off_t size = lseek(fd,0,SEEK_END); //查看文件大小
    lseek(fd,0,SEEK_SET);// 恢复文件指针

    char* buffer = (char*)malloc(size);
    ssize_t read_bytes = read(fd,buffer,size);
    if(read_bytes == -1){
        perror("read faild");
        free(buffer);
        return -1;
    }

    int stdout_fd = open("/dev/fd/1",O_WRONLY);
    if(stdout_fd == -1){
        return -1;
    }
    write(stdout_fd,buffer, size);
    // printf("%s",buffer);

    free(buffer);
    return 0;
}