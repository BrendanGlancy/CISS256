#include "header.h"
#include <stdio.h>

#include <stdio.h>

void gotoxy(int x, int y, int color_code) {
    printf("\033[%d;%dH", y, x);
    if (color_code != -1) {
        printf("\033[1;%dm", color_code);
    }
}

void resetTextColor() {
    printf("\033[0m");
}
