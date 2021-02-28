/*
    Program zawiera funkcji: tworzenia, otwierania, uzyskiwania wartosci, 
    operowania, zamykania i usuwania semafora
    =====================================================================
    Autor: Dmytro Boiko                                Krakow, 28.05.2020
*/
#include <sys/sem.h>          
#include <stdio.h>            
#include <stdlib.h>           
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

struct sembuf buf;

sem_t *semDecl(char * SEM_NAME) {
sem_t *sem;

  printf("Creating a semaphore %s\n", SEM_NAME);
  if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0777, 0)) == SEM_FAILED ) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  return sem;
}

sem_t *semO(char * SEM_NAME) {
sem_t *sem;

  printf("Accessing a semaphore %s\n", SEM_NAME);
  if ((sem = sem_open(SEM_NAME, 0)) == SEM_FAILED ) {
    perror("sem_open");
    exit(EXIT_FAILURE);
  }
  return sem;
}

void semP(sem_t *semid) {
  if ((sem_post(semid)) == -1) {
     perror("sem_post");
     exit(EXIT_FAILURE);
  }
}

void semInit(sem_t *semid, int val) {
/*
  if ((sem_init(semid, 0, val)) == - 1) {
    perror("sem_init");
    exit(EXIT_FAILURE);
  }
*/
  for (int i = 0; i < val; i++) semP(semid);
}

void semRm(sem_t *semid, char * SEM_NAME) {

  if ((sem_close(semid)) == -1) {
     perror("sem_close");
     exit(EXIT_FAILURE);
  }

  if (sem_unlink(SEM_NAME) == -1 ) {
    perror("sem_unlink");
    exit(EXIT_FAILURE);
  }
}

void semV(sem_t *semid) {
  if ((sem_wait(semid)) == -1) {
     perror("sem_wait");
     exit(EXIT_FAILURE);
  }
}

void semInfo(sem_t *semid, char * SEM_NAME) {
int value;

  if ((sem_getvalue(semid, &value)) == -1) {
     perror("sem_getvalue");
     exit(EXIT_FAILURE);
  }

  printf("%s = %d, addr: %p\n", SEM_NAME, value, (void *)semid);
}

void semInfo2(sem_t *semid, char * SEM_NAME) {
int value;

  if ((sem_getvalue(semid, &value)) == -1) {
     perror("sem_getvalue");
     exit(EXIT_FAILURE);
  }
  printf("%s = %d\n", SEM_NAME, value);
}
