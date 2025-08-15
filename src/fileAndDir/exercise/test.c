#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(){
    
        printf("OK %d",faccessat(AT_FDCWD,"../fileAndDir.md", X_OK  ,AT_EACCESS));
    
    printf ("%X",
        umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH));
    creat("bar",777);

    fchmodat(AT_FDCWD,"./bar",S_IRWXU | S_IRWXG | S_IRWXO,0);

    return 0;
}