/**
 * @file 3.c
 * @author rzzrz
 * @brief   从命令行参数获取源文件和目标文件名（如 ./copy src.txt dest.txt）
            将源文件内容完整复制到目标文件
            使用 1024 字节的缓冲区循环读写
            覆盖已存在的目标文件（使用 O_TRUNC）
 * @version 0.1
 * @date 2025-08-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc ,char ** argv){
    if(argc != 3)
    {
        printf("formatt : <source file> <destinate file path>\n");
        return -1;
    }

    int source_fd = open(argv[1],O_RDONLY);
    if(source_fd == -1){
        perror("open source file faild\n");
        return -1;
    }

    char buffer[1024];
    
    int dest_fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(dest_fd < 0){
        perror("open destnition file failed\n");
        close(source_fd);
        return -1;
    }

    ssize_t bytes_count = 0;
    while((bytes_count = read(source_fd,buffer,1024))){
        if(bytes_count == -1){
            perror("read file failed\n");
            break;
        }

        if(write(dest_fd,buffer,bytes_count) == -1){
            perror("write failed\n");
            break;
        }
    }

    close(source_fd);
    close(dest_fd);
    return 0;
}