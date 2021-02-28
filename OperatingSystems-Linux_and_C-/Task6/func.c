/*
    Plik func.c zawiera funkcje otwierania/odczytu/zapisu/zamykania pliku
    z obsluga bledow
    =====================================================================
    Autor: Dmytro Boiko                               Krakow, 10.05.2020
*/
#define SLEEP %999999
#define FILE_NAME "number.txt"

FILE *myopen(char *filename,char *mode) {
  FILE *f = fopen(filename,mode);
  if (f == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }
  return f;
}

int myread(FILE *fd) {
int digit;
  if (fread(&digit, sizeof(digit), 1, fd) < 0) {
     perror("Error read from file");
     exit(EXIT_FAILURE);
  }
  return digit;
}

void mywrite(int digit, FILE *fd) {
  if (fwrite(&digit, sizeof(digit), 1, fd) < 0) {
     perror("Error write to file");
     exit(EXIT_FAILURE);
  }
}

void myclose(FILE *fd) {
  if (fclose(fd) != 0) {
    perror("Error close file");
    exit(EXIT_FAILURE);
  }
}
