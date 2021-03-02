/*
    Biblioteka SEMAFOR
    ====================================================================
    Autor: Dmytro Boiko                               Krakow, 28.05.2020
*/
#include <semaphore.h>
#ifndef SEMHEHE_H
#define SEMHEHE_H
#define SEM_NAME1 "A"
#define SEM_NAME2 "B"

sem_t * semid1;
sem_t * semid2;

sem_t *semDecl(char * SEM_NAME);
sem_t *semO(char * SEM_NAME);
void semP(sem_t *semid);
void semV(sem_t *semid);
void semInit(sem_t *semid, int val);
void semRm(sem_t *semid, char * SEM_NAME);
void semInfo(sem_t *semid, char * SEM_NAME);
void semInfo2(sem_t *semid, char * SEM_NAME);

#endif 