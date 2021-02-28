/*
    Program przeznaczony dla wypisywanie odpowiednich komunikatow
    wypisywanych przez poszczegolne procesy. Takze program implementuje
    wzajemne wykluczanie w swojej sekcji krytycznej(odczytuje wartosc),a
    nastepnie zwieksza go o 1 i po pewnej chwili czasu zapisuje z powrotem
    do pliku.
    ======================================================================
    Autor: Dmytro Boiko                                Krakow, 10.05.2020
*/
#define _XOPEN_SOURCE 500
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

#include "func.c"
#include "sem.c"
#include "sem.h"


int main(int argc, char * argv[]) {
int x, sect_count, sync_flag;
pid_t pid;
FILE *fd = NULL;
//sprawdzania czy liczba argumentow jest poprawna
  if (argc != 2) {
    perror("ERROR argument");
    exit(EXIT_FAILURE);
  }
//Liczba sekcji
  sect_count = atoi(argv[0]);
//synchronizacja semaforow
  sync_flag = atoi(argv[1]); 
//ustawiamy sekwencje dla rand
  srand(time(NULL)); 
// PID procesu
  pid = getpid();
  s1 = s_open(SEM_NAME);
  for (int i = 0; i < sect_count; i++) {
    
//Przed sekcja krytyczna
    printf("PROCESS ID=%d before the critical section\n", pid);
    s_inf2(s1);
//Synchronizacja przez semafor
    if (sync_flag == 1) s_wait(s1);
    usleep(rand()SLEEP); 
//otwieramy plik dla czytania
    fd = myopen(FILE_NAME, "r+b");
//czytamy wartosc 
    x = myread(fd); 
    myclose(fd); 

//Sekcja krytyczna
    printf("=======> PROCESS ID=%d performs a critical section\n", pid);
    s_inf2(s1); 
    usleep(rand()SLEEP); 
//Zwiekszamy wartosc z pliku
    x++; 
//Otwieramy plik dla zapisu
    fd = myopen(FILE_NAME, "w+b"); 
//Zapisujemy nowa wartosc
    mywrite(x, fd); 
    myclose(fd);
    printf("=======> PROCESS ID=%d value from file=%d\n", pid, x);

//Po sekcji krytycznej
    if (sync_flag == 1) s_post(s1); 
    printf("PROCESS ID=%d after the critical section\n", pid);
    s_inf2(s1); 
    usleep(rand()SLEEP);  
  }
}
