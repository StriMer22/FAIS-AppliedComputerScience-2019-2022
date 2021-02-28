/*
    Zaimplementowanie problemu "Producenta i Konsumenta", przy pomocy programy, 
    ktory: utworzy potok nazwany, nastepnie przy pomocy funkcji fork() utworzy 
    dwa procesy potomne, w ktorych przy użyciu wywolania exec uruchomi odpowiednio 
    programy "producenta" i "konsumenta", a na koncu poczeka na ich zakonczenie i 
    usunie potok.
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 28.04.2020
    ------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 51 //rozmiar bufora

//funkcja wysylania komunikatu na stdout za pomoca write()
void msg(char *msg1, char *msg2, const int i){
char str[256];
   strcpy(str, "Producer: ");
   strcat(str, msg1); //str=msg1
//tablica bajtow w ciag dla wypisu
   if (i != 0) msg2[i] = 0; 
   strcat(str, msg2); //str=msg1+msg2
   strcat(str, "\n"); //str=str+\n
//wypisujemy на stdout
   write(STDOUT_FILENO, str, strlen(str));
}

int main(int argc, char *argv[]){
int file, size, i; 
int FIFO;
char buff[BUFFSIZE+1];
//sprawdzania czy liczba argumentow jest poprawna
   if (argc != 3){
     perror("To start enter: ./program_name <FILE_IN> <FIFO_NAME>\n");
     exit(EXIT_FAILURE);
   }
   char* FILE_IN = argv[1]; 
   char* FIFO_NAME = argv[2];
   msg("START", "", 0);
//ustawimy flag
   (void)umask(0);
//otworzmy plik tylko do czytania
   if ((file = open(FILE_IN, O_RDONLY)) < 0) { 
      perror("Error open FILE_IN for read\n");
      exit(EXIT_FAILURE);
   }
//otworzmy FIFO tylko do zapisu
   if ((FIFO = open(FIFO_NAME, O_WRONLY)) < 0){ 
     perror("Error open FIFO for writing\n");
     exit(EXIT_FAILURE);
   }
//czytamy dane z pipe(dopoki one tam istnieja)
   while((size = read(file, buff, BUFFSIZE)) > 0){
//wypisujemy, to, co przeczetalismy z pliku  
      msg("read from file: ", buff, size);
//Zapisujemy w FIFO
      if(write(FIFO, buff, size) == -1 ){
         perror("Error write to FIFO\n");
         exit(EXIT_FAILURE) ;
      }else{
//wypisujemy, to, co zapisalismy w FIFO 
      msg("write to fifo:  ", buff, size);
      }
//wygenerujemy pseudolosowa zmienna dla zatrzymania
      i = rand()%9; 
      sleep(i); 
   }
//zamykamy FILE_IN
   if (close(file)!=0){
      perror("Error close FILE_IN\n");
      exit(EXIT_FAILURE);
   }
//zamykamy FIFO
   if (close(FIFO)!=0){ 
      perror("Error close FIFO\n");
      exit(EXIT_FAILURE);
   }

   msg("STOP", "", 0);
   return 0; 
}