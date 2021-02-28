/*
    Biblioteka SEMAFOR
    ====================================================================
    Autor: Dmytro Boiko                               Krakow, 10.05.2020
*/
#include <semaphore.h>
#ifndef SEMHEHE_H
#define SEMHEHE_H

sem_t *s_open(char * S_NAME);
sem_t *s_create(char * S_NAME);
void s_init(sem_t *semid, int val);
void s_close(sem_t *semid);
void s_post(sem_t *semid);
void s_wait(sem_t *semid);
void s_tw(sem_t *semid);
void s_inf(sem_t *semid);
void s_inf2(sem_t *semid);

#endif 