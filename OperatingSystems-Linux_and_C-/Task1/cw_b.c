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
    int i;
    for(i = 0;i<3;i++){
//wywolania funkcji fork w petli for 
        switch(fork()){
//obsluga bledow
            case -1:
                perror("fork error");
                exit(1);
//proces potomny
            case 0:
		wypis_procesow();
		break;
//wywolania funkcji wait 
            default: 
                wait(0);
		break;
        };
    }
return 0;
}
