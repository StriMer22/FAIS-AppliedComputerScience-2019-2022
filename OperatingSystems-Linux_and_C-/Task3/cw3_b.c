/*
    Program, ktory za pomoca funkcji execl() uruchamia program(cw3_a.c) w procesie
    potomnym. Przyjmuje parametry z terminala przy uruchomieniu.
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 07.04.2020
    ------------------------------------------------------------------------------
*/
#define _XOPEN_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
    pid_t PID = 0;
//numer sygnalu
    int sig = atol(argv[2]);
//sprawdzania czy liczba argumentow jest poprawna
    if(argc !=3){
        printf("Number of count error");
        printf("To start enter: ./program_name <operation> <signal number>");
    }
    switch(fork()){
//obsluga bledow fork()
        case -1:
            perror("Fork error");
            exit(0);
            break;
        case 0:
//Uruchomienie programu cw3_a.c w procesie potomnym oraz obsluga bledow execl()
            PID = getpid();
            execl("./cw3_a.x","cw3_a", argv[1], argv[2], NULL);
            perror("Exec error");
            exit(1);
            break;
        default:
//Wysylania sygnalow poprzez funkcje kill()
            sleep(3);
            if(kill(PID,0) == 0){
                kill(PID,sig);
            }else{
                perror("No such process");
                exit(2);
            }
            break;
    }
return 0;
}