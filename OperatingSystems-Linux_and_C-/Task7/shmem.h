/*
    Biblioteka PAMIEC DZIELONA
    ====================================================================
    Autor: Dmytro Boiko                               Krakow, 28.05.2020
*/
#ifndef SHMEM_H
#define SHMEM_H

int shmCreate(char *SHM_NAME, int SIZE);
int shmOpen(char *SHM_NAME);
void shmRm(char * SHM_NAME);
void shmClose(int shmid);
char * shmAt(int shmid, int SIZE);
void shmDt(void *adres, int SIZE);

#endif 