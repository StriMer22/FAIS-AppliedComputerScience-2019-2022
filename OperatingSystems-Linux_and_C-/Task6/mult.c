/*
    Program do powielania procesow i weryfikajacy poprawnosc wzajemnego 
    wykluczania procesow - w oparciu o funkcje fork() i exec(). 
    ======================================================================
    Autor: Dmytro Boiko                                 Krakow, 10.05.2020
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <sys/wait.h>

#include "func.c"
#include "sem.c"
#include "sem.h"

int main(int argc, char * argv[]){
int i, child_count;
pid_t pid_main;
FILE *fd = NULL; 
//sprawdzania czy liczba argumentow jest poprawna
  if (argc != 5) {
    perror("usage: mult <worker_name> <count_workers> <count_critical> <sem_sync>");
    exit(EXIT_FAILURE);
  }
  pid_main = getpid();
  printf("MAIN PID=%d\n",pid_main);
//liczba uruchomionych workers
  child_count = atoi(argv[2]);
  fd = myopen(FILE_NAME, "w+b"); 
  i = 0; 
  mywrite(i, fd); 
  myclose(fd); 
  printf("The initial value of the file = %d\n", i);
//Usuwamy semafor
  sem_unlink(SEM_NAME); 
//Tworzymy semafor
  s1 = s_create(SEM_NAME); 
  printf("The initial value of the semaphore:\n");
//Informacja o semaforze1
  s_inf(s1);
//Inicjalizacja semafora
  s_init(s1, 1);
  printf("Initialized semaphore value:\n");
  s_inf(s1);
  for (i = 0; i < child_count; i++) {
     switch(fork()) {
     case -1: 
              perror("ERROR fork");
              exit(EXIT_FAILURE);
              break;
     case  0: 
              execl(argv[1], argv[3], argv[4], NULL);
              perror("ERROR execl");
              exit(EXIT_FAILURE);
              break;
     default: 
              break;
     }
   }

//oczekiwanie na zakonczenie procesow
  for (i = 0; i < child_count; i++) {
    if(wait(0)==-1){
      perror("wait error");
      exit(EXIT_FAILURE);
    }
  }
//zniszczenia semafora
  sem_close(s1);
  fd = myopen(FILE_NAME, "r+b");
  i = myread(fd); 
  myclose(fd); 
  printf("Final file value = %d\n", i);
//sprawdzanie liczby w pliku
  child_count = child_count * atoi(argv[3]);
  if (i == child_count) printf("All right\n");
  else printf("Wrong! Must be %d\n", child_count);

  return 0;
}