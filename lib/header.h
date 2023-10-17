#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>

void gotoxy(int x, int y, int color_code);
void resetTextColor();
void clearConsole();
void clearInputBuffer();

#ifdef __cplusplus
}
#endif

#endif // COMMON_H
