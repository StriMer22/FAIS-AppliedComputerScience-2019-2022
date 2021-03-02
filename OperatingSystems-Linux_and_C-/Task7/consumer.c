/*
     Program tworzy dowiazanie do pamieci dzielonej w celu pobrania z niej 
     danych, oraz tworzy powtornie semafor w celu sterowania dostepem do 
     pamieci dzielonej. Po pobraniu teksty, wyswietla go na ekranie.
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

typedef struct loop{
     int size;
     char bufor[SIZE];
} loop;

void consumer() {
     FILE *fp;
     int c_cnt = 0, i = 0, shmid;
     loop * buf;
     char c;
//otwieranie pliku output.txt do zapisu 
     if((fp = fopen("./output.txt", "w")) == NULL) {
          perror("fopen consumer");
          exit(EXIT_FAILURE);
     }
//pobieranie id semaforow 
     semid1 = semO(SEM_NAME1);
     semid2 = semO(SEM_NAME2);
//pobieranie id segmentu pamieci dzielonej 
     shmid = shmOpen(SHM_NAME);
//tworzenie dowiazania pamieci dzielonej 
     buf = (loop *)shmAt(shmid, sizeof(loop));
//cykl ciagly
     while(1) {
//czekamy dopiero semid2 != 0
          semV(semid2);
         
//zaczyna korzystać z pamięci dzielonej

          usleep(rand()%5555);

//zapis znaku z pamieci dzielonej do zmiennej c 
          c = buf->bufor[i%SIZE];
//jezeli c_cnt == buf->size, to wtedy nie ma nic wiecej do odczytania z bufora, przerwiemy cykl
          if (c_cnt == buf->size) break;
//semid1 = 1
          semP(semid1);
//zapis znaku ze zmiennej c do pliku output.txt 
          fputc(c, fp);
          sleep(1);
//wypisanie zapisanego znaku na ekran
          printf("Consumer write to output.txt %c\n", c);
          i++;
          c_cnt++;
     }
     if(fclose(fp) == EOF) {
          perror("fclose consumer");
          exit(EXIT_FAILURE);
     }
//usuniecie dowiazania segmentu pamięci dzielonej
     shmDt(buf, SIZE);
}

int main(int argc, char * argv[]) {
//sprawdza ilosc argumentow 
     if(argc != 1) {
          perror("number of arguments consumer.x");
          exit(EXIT_FAILURE);
     }
//zarodek dla randa
     srand(time(NULL));
     consumer();
     return 0;
}