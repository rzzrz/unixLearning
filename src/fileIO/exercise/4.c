/**
 * @file 4.c
 * @author rzzrz
 * @brief   打开一个文件（如 data.txt）
            将文件内容逆序写入新文件 reversed.txt
            使用 lseek 从后向前移动偏移量
            每次读取单个字符并写入目标文件
 * @version 0.1
 * @date 2025-08-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char ** argv){
    if(argc != 3){
        printf("formatt : <src file> <dest file>\n");
        return -1;
    }

    int src_fd = open(argv[1], O_RDONLY);
    if(src_fd == -1){
        perror("open file failed\n");
        return -1;
    }

    

    int dest_fd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC,0644);
    if(dest_fd == -1){
        perror("open dest file failed");
        close(src_fd);
        return -1;
    }

    off_t end = lseek(src_fd, 0, SEEK_END);
    char c;
    for(int i = end -1;i>=0;i--){
        lseek(src_fd, i, SEEK_SET);
        if(read(src_fd,&c,1) != 1){
            perror("read faild");
            break;
        }

        if(write(dest_fd,&c,1) != 1){
            perror("wirte faild");
            break;
        }
    }

    close(src_fd);
    close(dest_fd);
}