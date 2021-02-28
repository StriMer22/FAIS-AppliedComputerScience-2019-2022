#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//wypis identyfikatorow PID,PPID i PGID
void wypis_procesow(){
	printf("PID: %d | PPID: %d | PGID: %d\n",getpid(), getppid(), getpgrp());
}

int main() {
  int i;
  for (i = 0; i < 3; i++) {
//wywolania funkcji fork w petli for 
    switch (fork()) {
//proces potomny
      case 0: {
        break;
      }
//obsluga bledow
      case -1: {
        perror("fork error");
        exit(1);
      }
//wywolania funkcji sleep(oczekiwanie na proces potomny)
// oraz wypis procesow(grupowanie pokoleniami)
      default: {
        wypis_procesow();
        sleep(2 - i);
        break;
      }
    }
  }

  return 0;
}
