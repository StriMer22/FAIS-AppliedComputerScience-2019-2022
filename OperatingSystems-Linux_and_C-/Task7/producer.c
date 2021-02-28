/*
     Program tworzy pamiec dzielona o podanym  identyfikatorze, dowiazuje 
     do niej bufor cykliczny i  porcjami wrzuca do niego tekst pobierany 
     z pliku  input.txt. Wypisuje pobrany tekst, a nastepnie wrzuca go w bufor.
     =====================================================================
    Autor: Dmytro Boiko                                Krakow, 28.05.2020
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>      
#include <unistd.h>      
#include <time.h>
      
#include "shmem.h"
#include "sem.h"

#define SIZE 10
#define SHM_NAME "SHM_A"

typedef struct loop {
     int size;
     char bufor[SIZE];
} loop;

void producer() {
     FILE *fp;
     int i, shmid;
     loop * buf;
     char c;
//otwieranie pliku input.txt do odczytu
     if((fp = fopen("./input.txt", "r")) == NULL) {
          perror("fopen producer");
          exit(EXIT_FAILURE);
     }
//pobieranie id semaforow 
     semid1 = semO(SEM_NAME1);
     semid2 = semO(SEM_NAME2);
//pobieranie id segmentu pamieci dzielonej 
     shmid = shmOpen(SHM_NAME);
//tworzenie dowiązania pamięci dzielonej 
     buf = (loop *)shmAt(shmid, sizeof(loop));
//pętla działa dopoki fgetc nie zwroci konca pliku, pobiera znak z magazyn.txt i zapisuje do zmiennej c
     for(i = 0; (c = fgetc(fp)) != EOF; i++) {
//czekamy dopiero semid1 != 0
          semV(semid1);

//zaczyna korzystać z pamięci dzielonej

          usleep(rand()%5555);
//zapisanie znaku c w pamięci dzielonej
          buf->bufor[i%SIZE] = c;
//zwiekszenie o 1 licznika ilości znakow zapisanych w pamieci dzielonej
          buf->size++;
//semid2 = 1
          semP(semid2);
          sleep(1);
//wypisanie na ekran znaku zapisanego w pamięci dzielonej
          printf("Producer read from input.txt %c\n", c);
     }
//zwiekszenie wartosci semafora, aby konsument zakonczyl cykl
     semP(semid2);
     if(fclose(fp) == EOF) {
          perror("fclose producer");
          exit(EXIT_FAILURE);
     }
//usuniecie dowiazania segmentu pamięci dzielonej
     shmDt(buf, SIZE);
}

int main(int argc, char * argv[]) {
//sprawdza ilosc argumentow 
     if(argc != 1) {
          perror("number of arguments producer.x");
          exit(EXIT_FAILURE);
     }
//zarodek dla randa
     srand(time(NULL));
     producer();
     return 0;
}