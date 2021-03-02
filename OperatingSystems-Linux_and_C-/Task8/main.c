/*
    Zaimplementowanie zadania wzajemnego wykluczania dla watkow. Watek wykonuje
    swoja sekcje prywatna, wypisuje komunikat po lewej stronie okna konsoli, a w 
    sekcji krytycznej drukuje informacje po prawej stronie. Do zademonstrowania
    operacji na zasobie dzielonym uzyto wspolnej zmiennej licznikowej.
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 09.06.2020
    ------------------------------------------------------------------------------
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SLEEP %7
// ogólna (globalna) zmienna licznika
static int counter=0; 
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int CYCLE_COUNT;
int THREAD_COUNT;

void* Thread(void *p) {
int i, x; 
int * j = (int *)p;
    sleep(1);
    for (i = 0; i < CYCLE_COUNT; i++) {
        printf("\033[4CThread # %d: Private section # %d\033[0m\n", *j, i);
        sleep(rand()SLEEP); 
//krytyczna sekcja
        pthread_mutex_lock(&mutex);
        printf("\033[40C\033[0;97m\033[41mThread # %d: Critical section # %d\033[0m\n", *j, i);
        x = counter;
        x++;
//usypianie
        usleep(rand()SLEEP); 
        counter = x;
        pthread_mutex_unlock(&mutex);
    }
    printf("\033[47m\033[1;94m\033[4CThread # %d: shot down\033[0m\n", *j);
    return 0;
}

int main(int argc, char * argv[]) {
//sprawdzanie ilosci argumentow
     if(argc != 3) {
          perror("ERROR argv count");
          printf("usage: %s THREAD_COUNT CYCLE_COUNT\n", argv[0]);
          exit(EXIT_FAILURE);
     }
//ilosc potokow
    THREAD_COUNT = atoi(argv[1]);
//ilosc petli
    CYCLE_COUNT = atoi(argv[2]); 
   pthread_t thread[THREAD_COUNT];
   int i,j[THREAD_COUNT];
//ustawienie poczatkowej wartosci generatora liczb pseudolosowych
    srand(time(NULL));
//Clear the screen       
    system("clear");         
//tworzenia mutexa
    pthread_mutex_init(&mutex, NULL);
//Adres mutexa
    printf("\033[0;107m\033[1;90m*** mutex addr = %p created\033[0m\n", (void *)&mutex);
    puts("");
//tworzenie watkow
    for (i=0; i<THREAD_COUNT; i++){
       j[i] = i;
      pthread_create(&thread[i], NULL, Thread, &j[i]);
      printf(">>> Thread created # %d ID %ld\n", i, thread[i]);
    }
    puts("");
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread[i], NULL);
    }
    puts("");
//oczekiwana wartość licznika
    i = THREAD_COUNT * CYCLE_COUNT; 
    printf("Counter value = %d (must be = %d)\n", counter, i);
    if (counter == i) puts("The counter value is correct.");
    else puts("Counter value is incorrect");
//Usuwanie muteksa
    printf("\033[0;107m\033[1;90m*** mutex addr = %p deleted\033[0m\n", (void *)&mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}