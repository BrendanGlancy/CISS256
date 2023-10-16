#ifndef COMMON_H
#define COMMON_H

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

void gotoxy(int x, int y, int color_code) {
  printf("\033[%d;%dH", y, x);
  if (color_code != -1) {
    printf("\033[1;%dm", color_code);
  }
}

void resetTextColor() { printf("\033[0m"); }

void clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

#endif // COMMON_H
