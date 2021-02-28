/*
    Program, ktory uruchamia grupe procesow i wysyla do niej sygnaly.Przyjmuje 
    parametry z terminala przy uruchomieniu.
    ------------------------------------------------------------------------------
    Autor: Dmytro Boiko                                         Krakow, 07.04.2020
    ------------------------------------------------------------------------------
*/
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define max_proc 4
#define SIGNAL "2"

int my_number, stat, corp;
pid_t child[max_proc], child_pid, pgid;

int main(int argc, char* argv[]){

  // rodzic ignore sygnalu 2
  signal(SIGINT, SIG_IGN);

  // stworzymy max_proc potomkow
  // 0 - potomny lider grupy
  for (int i = 0; i < max_proc; ++i) {
    child_pid = fork();
    child[i] = child_pid;
    if (child[i] == 0) {
        my_number = i;
        if (my_number == 0) {
          // Tworzymy lidera grupy
          setpgid(0, 0);
          // ignore sygnalu 2
          signal(SIGINT, SIG_IGN);
        }
        break;
    } else {
      // proces macierzysty
    }
  }

  if (child_pid == 0) {
    // proces potomny
    if (my_number != 0) {
      execl("./cw3_a.x","cw3_a", argv[1], argv[2], NULL);
    }
  } else {
    // proces macierzysty
    sleep(1);
    pgid = getpgid(0);
    puts("Parent send signal");
    kill(-pgid, SIGINT);

    // oczekujemy na ukonczenie procesu potomneto
    // pokazujemy kody wyjscia
    while ((corp=wait(&stat)) > 0) {
      printf("exit code = %d\n", WEXITSTATUS(stat));
    }
  }
}

