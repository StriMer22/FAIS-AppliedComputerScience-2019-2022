/*
    Zaimplementowanie problemu "Producenta i Konsumenta", przy pomocy programy, 
    ktory: utworzy potok nazwany, nastepnie przy pomocy funkcji fork() utworzy 
    dwa procesy potomne, w ktorych przy użyciu wywolania exec uruchomi odpowiednio 
    programy "producenta" i "konsumenta", a na koncu poczeka na ich zakonczenie i 
    usunie potok. Potok nazwany tworzymy z poziomu powloki(uruchomienia programu 
    z roznych terminali), na koncu usuwamy ten
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 28.04.2020
    ------------------------------------------------------------------------------
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

//funkcja wysylania komunikatu na stdout za pomoca write()
void msg(char *msg){
char str[256];
   strcpy(str, "Main: ");
   strcat(str, msg);
   strcat(str, "\n");
//wypisujemy на stdout
   write(STDOUT_FILENO, str, strlen(str)); 
}

int main(int argc, char *argv[]){
int i, my_number; 
pid_t child_pid;
//sprawdzania czy liczba argumentow jest poprawna
   if (argc != 4){
     perror("To start enter: ./program_name <FILE_IN> <FILE_OUT> <FIFO_NAME>\n");
     exit(EXIT_FAILURE);
   }
   char* FILE_IN = argv[1];
   char* FILE_OUT = argv[2];
   char* FIFO_NAME = argv[3];

   msg("START");
//usuwamy plik fifo
   unlink(FIFO_NAME); 
//tworzymy fifo
   if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) < 0){ 
     perror("Error create FIFO\n");
     exit(EXIT_FAILURE);
   }
//tworzymy dwa procesy potomne
   for (i=0; i<2; i++){ 
      if ((child_pid = fork()) < 0){
         perror("Error exec fork\n");
         exit(EXIT_FAILURE);
      }
      if (child_pid == 0) {
         my_number = i;
         break;
      }
   }
   if (child_pid == 0){
      switch(my_number){ 
         case 0: 
               msg("exec producer..."); 
//call producer
               execl("producer.x", "", FILE_IN, FIFO_NAME, NULL);
               break;
         case 1: 
               msg("exec consumer...");
//call consumer 
               execl("consumer.x", "", FILE_OUT, FIFO_NAME, NULL);
               break;
      }
   }else if(wait(0)==-1){
      perror("wait error");
      exit(EXIT_FAILURE);
   }
//usuwamy plik fifo
   unlink(FIFO_NAME);
   msg("STOP"); 
   return 0; 
}
