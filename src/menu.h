#ifndef MENU_H
#define MENU_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include "../lib/header.h"

void welcome();
void displayMenu();
void configCarPrompt();
int getChoice();
void infoHeader(char message[]);

#ifdef __cplusplus
}
#endif

#endif // MENU_H
