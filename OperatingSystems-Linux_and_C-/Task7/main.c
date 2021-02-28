/*
     Zaimplementowanie problemu "Producenta i Konsumenta", przy pomocy pamieci
     dzielonej oraz semaforow standardu POSIX. Zamiast potoku uzyto N-elementowego
     bufora cyklicznego umieszczonego w pamieci dzielonej, gdzie elementem bufora 
     jest pewna ustalona porcja bajtow. Dostep do wspolnego bufora synchronizowany 
     przy pomocy semaforow.
     ===========================================================================
    Autor: Dmytro Boiko                                     Krakow, 28.05.2020
*/
#include <stdio.h>
#include <unistd.h>      
#include <stdlib.h> 
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/mman.h>

#include "sem.h"
#include "shmem.h"

#define SIZE 10
#define SHM_NAME "SHM_A"

typedef struct loop {
     int size;
     char bufor[SIZE];
} loop;

int main(int argc, char * argv[]) {
//sprawdza ilość argumentow 
     if(argc != 1) {
          perror("ERROR count");
          exit(EXIT_FAILURE);
     }
     sem_t * semid1;
     sem_t * semid2;
     int shmid;
//tworzy 2 semafory 
     semid1 = semDecl(SEM_NAME1);
     semid2 = semDecl(SEM_NAME2);
//inicjalizuje semafor 1 wartością 1
     semInit(semid1, 1);
//inicjalizuje semafor 2 wartością 0
     semInit(semid2, 0);
//Wypisujemy wartosc i adres semafora
     semInfo(semid1,SEM_NAME1);
     semInfo(semid2,SEM_NAME2);
//tworzy pamięć dzieloną
     shmid = shmCreate(SHM_NAME, sizeof(loop));
//tworzy proces potomny producer.x
     switch(fork()) {
          case -1:
               perror("fork error");
               exit(EXIT_FAILURE);
               break;
          case 0:
               execl("./producer.x", "./consumer.x", NULL);
               perror("execl p");
               exit(EXIT_FAILURE);
               break;
          default:
               sleep(1);
               break;
     }
//tworzy proces potomny consumer.x 
     switch(fork()) {
          case -1:
               perror("fork error 2");
               exit(EXIT_FAILURE);
               break;
          case 0:
               execl("./consumer.x", "./producer.x", NULL);
               perror("execl k");
               exit(EXIT_FAILURE);
               break;
          default:
               break;
     }
//proces macierzysty czeka na 2 procesy potomne 
     for(int i = 0; i < 2; i++){
          if(wait(0)==-1){
               perror("wait error");
               exit(EXIT_FAILURE);
          }
     }
//usuniecie semaforow
     semRm(semid1, SEM_NAME1);
     semRm(semid2, SEM_NAME2);
//usuniecie segmentu pamieci dzielonej
     shmClose(shmid);
     shmRm(SHM_NAME);
//sprawdza czy pliki sa takie same
     system("diff -s input.txt output.txt");
     return 0;
}