#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//wypis identyfikatorow UID,GID,PID,PPID i PGID
void wypis_procesow(){
    printf("UID: %d | GID: %d | PID: %d | PPID: %d | PGID: %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
}
int main(){
        wypis_procesow();
    return 0;
}
