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
   strcpy(str, "Consumer: ");
   strcat(str, msg1); // str=msg1
//tablica bajtow w ciag dla wypisu
   if (i > 0) msg2[i] = 0; 
   strcat(str, msg2); // str=msg1+msg2
   strcat(str, "\n"); // str=str+\n
//wypisujemy на stdout
   write(STDOUT_FILENO, str, strlen(str)); 
}

int main(int argc, char *argv[]){
int i, file, size, FIFO;
char buff[BUFFSIZE+1];
//sprawdzania czy liczba argumentow jest poprawna
   if (argc != 3){
     perror("To start enter: ./program_name <FILE_OUT> <FIFO_NAME>\n");
     exit(EXIT_FAILURE);
   }
   char* FILE_OUT = argv[1]; 
   char* FIFO_NAME = argv[2];
   msg("START","", 0); 
//zerujemy masku tworzenie plikow dla biezacego procesu
   (void)umask(0); 
//otworzmy plik/jesli juz istnieje, przyciac go do zerowej dlugosci 
   if ((file = open(FILE_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0){ 
      perror("Error open FILE_OUT for writing\n");
      exit(EXIT_FAILURE);
   }
//otworzmy fifo dla czytania
   if ((FIFO = open(FIFO_NAME, O_RDONLY)) < 0){ 
      perror("Error open FIFO\n");
      exit(EXIT_FAILURE);
   }
//czytamy dane z fifo(dopoki one tam istnieja)
   while ((size = read(FIFO, buff, BUFFSIZE)) > 0 ){ 
      msg("read from fifo: ", buff, size); 
//zapisujemy do pliku zawartosc buff
      if (write(file, buff, size) < 0){
         perror("Error write to FILE_OUT\n");
         exit(EXIT_FAILURE);
//wypisujemy, to, co zapisalismy do pliku
      } else msg("write to file:  ", buff, size);
//wygenerujemy pseudolosowa zmienna dla zatrzymania
      i = rand()%9; 
      sleep(i);
   } msg("fifo is empty","", 0);
//zamykamy FILE_OUT
   if (close(file)!=0){
      perror("Error close FILE_OUT\n");
      exit(EXIT_FAILURE);
   }
//zamykamy fifo
   if (close(FIFO)!=0){
      perror("Error close FIFO\n");
      exit(EXIT_FAILURE);
   }
   msg("STOP","", 0);
   return 0;
}