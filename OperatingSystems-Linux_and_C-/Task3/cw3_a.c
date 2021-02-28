/*
    Program do obslugi sygnalow. Przyjmuje parametry z terminala przy uruchomieniu
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 07.04.2020
    ------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

//wlasny sig_handler
extern const char * const sys_siglist[];
void handler(int syg){
  printf("\nSignal nr: %d | Signal name: %s\n",syg,sys_siglist[syg]);
}

int main(int argc, char *argv[]){
//printf("child start");
//sprawdzania czy liczba argumentow jest poprawna
// printf("argc=%d\n", argc);
    if(argc != 3){
        printf("Number of count error\n");
        printf("To start enter: ./program_name <operation> <signal number>\n");
        exit(EXIT_FAILURE);
    }

//sekwencja klawisz
    char* key_bindings = argv[1];

//numer sygnalu
    int sig = atol(argv[2]);

//dzialanie domyslne
    if(strcmp((key_bindings), "default") == 0){
        if(signal(sig, SIG_DFL) == SIG_ERR){
            perror("Operation failed\n");
            exit(EXIT_FAILURE);
        }

//ignorowanie
    }else if(strcmp((key_bindings), "ignore") == 0){
        if(signal(sig, SIG_IGN) == SIG_ERR){
            perror("Operation failed\n");
            exit(EXIT_FAILURE);
        }

//wlasna obsluga bledow
    }else if(strcmp((key_bindings), "signal_handler") == 0){
        if(signal(sig,handler) == SIG_ERR){
            perror("Operation failed\n");
            exit(EXIT_FAILURE);
        }
    }else{
       printf("Wrong value\n");
       exit(EXIT_FAILURE);
    }

//Wypis procesu PID
    //printf("\nAction: %s\nNumber of signal: %d, in process\nPID: %d\n", key_bindings, sig, getpid());
    printf("\nAction: %s\nNumber of signal: %d, in process\nPID: %d\n\n", key_bindings, sig, getpid());

//oczekiwanie na sygnal
    //puts("wait signal...");
    pause();
    //puts("receiv signal...");

return 0;
}