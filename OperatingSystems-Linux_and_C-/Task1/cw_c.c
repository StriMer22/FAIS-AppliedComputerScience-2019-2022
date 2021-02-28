#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//wypis identyfikatorow PID,PPID i PGID
void wypis_procesu(){
    printf("PID: %d | PPID: %d | PGID: %d\n",getpid(),getppid(),getpgrp());
}

int main(){
    wypis_procesu();
    int i;
    for (i=0;i<3;i++){
//wywolania funkcji fork w petli for 
        switch(fork()){
//obsluga bledow
            case -1:
                perror("fork error");
                exit(1);
//proces potomny oraz uzycie funkcji sleep 
            case 0:
		sleep(i+1);
		wypis_procesu();
		break;
            default:
                break;
        };
    }
return 0;
}
