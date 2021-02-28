#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//wypis identyfikatorow UID,GID,PID,PPID i PGID
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
//proces potomny, zrobienia z kazdego procesu dziecka lider wlasnej grupy 
            case 0:
		sleep(i+1);
		setpgid(getpid(), 0);
		wypis_procesu();
		break;
//Drugie wywolania funkcji sleep(oczekiwanie na proces potomny)
            default:
		sleep(7);
                break;
        };
    }
return 0;
}
