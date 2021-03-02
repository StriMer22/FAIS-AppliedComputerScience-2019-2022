/*
    Program zawiera funkcji: tworzenia, otwierania, uzyskiwania dostepu, 
    usuwania segmentu, dowiazania segmentu pamieci dzielonej
    =====================================================================
    Autor: Dmytro Boiko                                Krakow, 28.05.2020
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>            
#include <sys/types.h>              
#include <sys/shm.h>          
#include <stdlib.h>           
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

int shmCreate(char *SHM_NAME, int SIZE) {
int shmid;
    if ((shmid = shm_open(SHM_NAME, O_RDWR | O_CREAT | O_EXCL, 0666)) == -1) {
       perror("shmCreate shm_open");
       exit(EXIT_FAILURE);
     }
     if ( ftruncate(shmid, SIZE + 1) == -1 ) {
         perror("shmCreate ftruncate");
         return 1;
     }
     return shmid;
}

int shmOpen(char *SHM_NAME) {
int shmid;
    if ((shmid = shm_open(SHM_NAME, O_RDWR, 0666)) == -1) {
       perror("shmOpen");
       exit(EXIT_FAILURE);
     }

    return shmid;
}

void shmRm(char * SHM_NAME) {

     if(shm_unlink(SHM_NAME) <0) {
          perror("shmRm");
          exit(EXIT_FAILURE);
     }
}

void shmClose(int shmid) {

     if (close(shmid) < 0) {
          perror("shmClose");
          exit(EXIT_FAILURE);
     }
}

char * shmAt(int shmid, int SIZE) {
char * adres;

    adres = mmap(0, SIZE+1, PROT_WRITE|PROT_READ, MAP_SHARED, shmid, 0);
    if ( adres == (char*)-1 ) {
        perror("shmAt");
        exit(EXIT_FAILURE);
    }
     return adres;
}

void shmDt(void *adres, int SIZE) {

     if (munmap(adres, SIZE) < 0) {
          perror("shmDt");
          exit(EXIT_FAILURE);
     }
}
