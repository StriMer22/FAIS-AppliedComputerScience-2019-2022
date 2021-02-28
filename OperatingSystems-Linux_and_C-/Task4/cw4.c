/*
    Zaimplementowanie problemu "Producenta i Konsumenta", przy pomocy programy, 
    ktory: tworzy ninazwany potok do komunikacji miedzy producentem a konsumentem;
    Producent przesyła fragmentami zawartość pliku tekstowego do potoku, a 
    Konsument odczytuje zawartość potoku i zapisuje do innego pliku tekstowego
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 21.04.2020
    ------------------------------------------------------------------------------
*/

#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 40 // rozmiar bufora
#define FILE_IN "file_in.txt" // input file
#define FILE_OUT "file_out.txt" // output file
#define MAXSLEEP 9 // dla losowego czasu usypiania

//funkcja konwersji liczby na ciag(string)
char* itostr(int val){
static char buf[12] = {0};
int i = 10;
   for(; val && i ; --i, val /= 10)
      buf[i] = "0123456789"[val % 10];
   return &buf[i+1];
}

//funkcja wysylania komunikatu na stdout za pomoca write()
void msg(const char *msg1, const char *msg2, const int i){
   char newstr[6];
   write(STDOUT_FILENO, msg1, strlen(msg1)); 
   write(STDOUT_FILENO, msg2, strlen(msg2)); 
//jesli jest liczba, przeksztalcimy ja na ciag(string) i wypiszmy na stdout
   if (i > 0){ 
      strcpy(newstr, itostr(i)); 
      write(STDOUT_FILENO, newstr, strlen(newstr)); 
   }
//10 - znak przeniesienia ciagu(string)
   newstr[0]=10; 
//wypisujemy на stdout przeniesienia ciagu(string)
   write(STDOUT_FILENO, newstr, 1); 
}

//Konsument
void receiver(int * fd){
int i, size, file; 
char buff[BUFFSIZE];  
//zamknijmy nie uzywany dyskrypter 1
   close(fd[1]); 
//zerujemy masku tworzenie plikow dla biezacego procesu
   (void)umask(0); 
//otworzmy plik/jesli juz istnieje, przyciac go do zerowej dlugosci  
   if ((file = open(FILE_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0){ 
      perror("Error open file: ");
      exit(EXIT_FAILURE);
   }
//czytamy dane z pipe(dopoki one tam istnieja)
   while ((size = read(fd[0], buff, BUFFSIZE)) > 0 ){ 
//jesli przeczytano mniej, czym maksymalny rozmiar bufora, to zmienimy rozmiar
      if (size < BUFFSIZE) buff[size]=0; 
//wypisujemy, to, co przeczetalismy z pipe  
      msg("Receiver read from pipe: ", buff, 0); 
//zapisujemy do pliku zawartosc buff
      if (write(file, buff, strlen(buff)) < 0) { 
         perror("Error write to file: ");
         exit(EXIT_FAILURE);
//wypisujemy, to, co zapisalismy do pliku
      } else msg("Receiver write to file:  ", buff, 0); 
//wygenerujemy pseudolosowa zmienna dla zatrzymania    
      i = rand()%MAXSLEEP; 
      msg("Receiver sleep = ","", i);
      sleep(i);
   }
//komunikat, ze pipe jest pusty
   msg("Receiver:"," pipe is empty", 0); 
//zamykamy FILEOUT
   close(file); 
//zamykamy pipe
   close(fd[0]); 
//komunikat o zakonczeniu dzialalnosci konsumenta
   msg("Receiver: ","STOP", 0); 
}

//Producent
void sender(int * fd){
int file, i, size;
char buff[BUFFSIZE]; 
//zamknijmy nie uzywany dyskrypter 0
   close(fd[0]); 
//ustawimy flag
   (void)umask(0); 
//otworzmy plik tylko do czytania
   if ((file = open(FILE_IN, O_RDONLY)) < 0){ 
      perror("Error open file: ");
      exit(EXIT_FAILURE);
   }
//czytamy z pliku
   while ((size = read(file, buff, BUFFSIZE)) > 0){ 
      if (size < BUFFSIZE) buff[size]=0;
//wypisujemy, to, co przeczytalismy z pliku
      msg("Sender read from file: ", buff, 0); 
//zapisujemy w pipe
      if (write(fd[1], buff, strlen(buff)) == -1 ){ 
         perror("Error write to pipe\n");
         exit(EXIT_FAILURE) ;
      } 
//wypisujemy, to, co zapisalismy w pipe
      msg("Sender write to pipe:  ", buff, 0); 
//wygenerujemy pseudolosowa zmienna dla zatrzymania
      i = rand()%MAXSLEEP; 
      msg("Receiver sleep = ","", i);
      sleep(i); 
   }
//zamykamy FILE_IN
   close(file); 
//zamykamy pipe
   close(fd[1]); 
}

int main(){
//deskryptory plikow
int fd[2];
//obsluga bledow dla potoku
   if (pipe(fd) == -1){ 
      perror("Error create pipe\n");
      exit(EXIT_FAILURE);
   }
   switch(fork()){ 
//obsluga bledow fork()
      case -1: 
         perror("Error fork\n");
         exit(EXIT_FAILURE);
//proces potomny - konsument
      case 0:  
         receiver(fd); 
         break;
      default: 
//proces macierzysty - producent
         sender(fd); 
//oczekiwania na zakonczenie procesu potomnego
         if(wait(0) == -1){
            perror("wait error");
            exit(EXIT_FAILURE);
         }; 
//komunikat o zakonczeniu dzialalnosci producenta
         msg("Sender: STOP","", 0);  
         break;
   }
   return 0; 
}