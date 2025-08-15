/**
 * @file 5.c
 * @author rzzrz
 * @brief   打开文件 data.txt
            从偏移量 10 开始覆盖写入字符串 "MODIFIED"
            确保不改变文件其他部分（使用 O_RDWR 标志）
            如果偏移量超出文件大小，用 0 填充空隙
 * @version 0.1
 * @date 2025-08-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(){
    int fd = open("./data.txt",O_RDWR,0644);
    if(fd == -1){
        perror("open file failed");
        return -1;
    }

    off_t size = lseek(fd,0, SEEK_END);
    off_t offset = 10;

    if(offset > size){
        for(int i = size;i<offset;i++){
            if(write(fd,"\0", 1) != 1){
                perror("write failed\n");
                close(fd);
                return -1;
            }
        }
    }

    lseek(fd,offset,SEEK_SET);

    char * msg = "MODIFIED";
    if(write(fd,msg,strlen(msg)) == -1){
        perror("write failed\n");
        close(fd);
        return -1;
    }

    close(fd);
}