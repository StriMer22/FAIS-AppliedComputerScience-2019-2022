/*
    Program tworzacy procesy potomne i uruchamiajacy w nowej programie za pomoca funkcji fork() oraz exec()
    -------------------------------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                                                  Krakow, 24.03.2020
    -------------------------------------------------------------------------------------------------------                           
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//wypis identyfikatorow UID,GID,PID,PPID i PGID
void wypis_procesow(){
    printf("UID: %d | GID: %d | PID: %d | PPID: %d | PGID: %d\n",getuid(),getgid(),getpid(),getppid(),getpgrp());
}

int main(int argc, char* argv[]){
    wypis_procesow();
    printf("\n");
    int i;
//sprawdzania czy liczba argumentow jest poprawna
    if(argc != 3){
        perror("number of count error");
        exit(1);
    }
    for(i = 0;i < 3;i++){
//wywolania funkcji fork w petli for
        switch(fork()){
//obsluga bledow fork()
            case -1:
                perror("fork error");
                exit(2);
//wywolania funkcji exec(z argumentami) w procesie potomnym oraz sprawdzania bledow exec
            case 0:
		        execl(argv[1],argv[2],NULL);
                perror("exec error");
                exit(3);
		    break;
            default:
//wywolania funkcji sleep() z krotkim czasem w procesie macierzystym
                sleep(2);
		    break;
        };
    }
//wywolania funkcji wait() w nowej petli dla oczekiwania zakonczenia tylko jednego procesu
//oraz obluga bledow dla funkcji wait()
    for(i = 0;i < 3;i++){
        if(wait(0) == -1){
            perror("wait error");
        }
    }
return 0;
}
