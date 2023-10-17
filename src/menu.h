#ifndef MENU_H
#define MENU_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "../lib/header.h"

void welcome();
void displayMenu();
void configCarPrompt();
void exitprog();
int getChoice();
void infoHeader(int carObjCount);

#ifdef __cplusplus
}
#endif

#endif // MENU_H
