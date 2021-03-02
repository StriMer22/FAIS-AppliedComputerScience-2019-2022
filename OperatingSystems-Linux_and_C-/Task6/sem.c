/*
    Program zawiera funkcji: tworzenia, otwierania, uzyskiwania wartosci, 
    operowania, zamykania i usuwania semafora
    =====================================================================
    Autor: Dmytro Boiko                                Krakow, 10.05.2020
*/
#include "sem.h"
#define SEM_NAME "Semaphore value"
sem_t * s1;

void s_unlink(char * S_NAME) {
  if (sem_unlink(S_NAME) == -1 ) {
    perror("Error s_unlink");
    exit(EXIT_FAILURE);
  }
}
sem_t *s_create(char * S_NAME) {
sem_t *sem;
  printf("Creating a semaphore\n");
  if ((sem = sem_open(S_NAME, O_CREAT | O_EXCL, 0777, 0)) == SEM_FAILED ) {
    perror("Error s_create");
    exit(EXIT_FAILURE);
  }
  return sem;
}
sem_t *s_open(char * S_NAME) {
sem_t *sem;
  printf("Getting access to semaphore\n");
  if ((sem = sem_open(S_NAME, 0)) == SEM_FAILED ) {
    perror("Error s_open");
    exit(EXIT_FAILURE);
  }
  return sem;
}
void s_close(sem_t *semid) {
  if ((sem_close(semid)) == -1) {
     perror("Error s_close");
     exit(EXIT_FAILURE);
  }
}
void s_inf(sem_t *semid) {
int value;
  if ((sem_getvalue(semid, &value)) == -1) {
     perror("Error s_inf");
     exit(EXIT_FAILURE);
  }
  printf("%s = %d, Addr: %p\n", SEM_NAME, value, (void *)semid);
}
void s_inf2(sem_t *semid) {
int value;
  if ((sem_getvalue(semid, &value)) == -1) {
     perror("Error s_inf2");
     exit(EXIT_FAILURE);
  }
  printf("%s = %d\n", SEM_NAME, value);
}
void s_post(sem_t *semid) {
  if ((sem_post(semid)) == -1) {
     perror("Error s_post");
     exit(EXIT_FAILURE);
  }
}
void s_wait(sem_t *semid) {
  if ((sem_wait(semid)) == -1) {
     perror("Error s_wait");
     exit(EXIT_FAILURE);
  }
}
void s_tw(sem_t *semid) {
  if ((sem_trywait(semid)) == -1) {
     perror("s_tw");
     exit(EXIT_FAILURE);
  }
}
void s_init(sem_t *semid, int val) {
  /*
  if ((sem_init(semid, 0, val)) == - 1) {
    perror("Error s_init");
    exit(EXIT_FAILURE);
  }
  */
  for (int i = 0; i < val; i++) s_post(s1);
}
