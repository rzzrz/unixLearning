/**
 * @file 3.2.c
 * @author rzzrz
 * @brief 实现一个和dup2一样的函数,要求不带有fcntl,并且做出正确错误处理
 * @version 0.1
 * @date 2025-08-13
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <asm-generic/errno.h>
#include <cerrno>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

/**
 * @brief 实现dup2功能
 *
 * @param olddf 指定的文件
 * @param newdf 期望得到的文件描述符
 * @return int
 */
int my_dup2(int oldfd, int newfd) {
  if (oldfd < 0 || newfd < 0) {
    errno = EBADFD;
    return -1;
  }

  if (oldfd == newfd)
    return oldfd;
  if (close(newfd) < 0)
    printf("error closing file");

  int *fds;

  int count = 0; // fd数组大小

  int refd = 0, status = 0;
  while (1) {
    int fd = dup(oldfd);
    if (fd == newfd) {
      refd = fd;
      break;
    }

    if (fd == -1)
      continue;

    if(fd > newfd){
        close(fd);
        continue;
    }
        

    int *new_fds = (int *)realloc(fds, sizeof(int) * (count + 1));
    if (!new_fds) {
      status = -1;
      close(fd);
    }
    fds = new_fds;
    fds[count++] = fd;
  }

  for (int i = 0; i < count; i++) {
    close(fds[i]);
  }

  free(fds);
  return status == -1 ? -1 : refd;
}


int main() { return 0; }