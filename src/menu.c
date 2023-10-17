#include "menu.h"
#include "../lib/header.h"
#include <stdio.h>

void welcome() {
  clearConsole();
  gotoxy(5, 0, 36);
  printf("-----------------------------------------------------"
         "------------");
  gotoxy(5, 2, 36);
  printf(" __          __    _                               _ ");
  gotoxy(5, 3, 36);
  printf(" \\ \\        / /   | |                             | |");
  gotoxy(5, 4, 36);
  printf("  \\ \\  /\\  / /___ | |  ___  ___   _ __ ___    ___ | |");
  gotoxy(5, 5, 36);
  printf("   \\ \\/  \\/ // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\| |");
  gotoxy(5, 6, 36);
  printf("    \\  /\\  /|  __/| || (__| (_) || | | | | ||  __/|_|");
  gotoxy(5, 7, 36);
  printf("     \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|(_)");
  gotoxy(5, 8, 36);
  printf("                                                     ");
  gotoxy(5, 9, 36);
  printf("---------------------------------------------------------------"
         "--\n");
}

void displayMenu() {
  gotoxy(5, 11, 33);
  printf(">>>> MAIN MENU <<<<");
  gotoxy(5, 13, 32);
  printf("1. Configure a vehicle");
  gotoxy(5, 14, 32);
  printf("2. Save Configured vehicle");
  gotoxy(5, 15, 32);
  printf("3. View Stored Orders");
  gotoxy(5, 16, 31);
  printf("4. Exit");
  gotoxy(5, 18, 34);
  printf("Enter your choice: ");
}

void configCarPrompt() {
  clearConsole();
  gotoxy(0, 2, 36);
  printf("=================================================");
  gotoxy(0, 4, 36);
  printf("---=                 Hello                   =---");
  gotoxy(0, 6, 36);
  printf("---=  Please Enter your Vehicle Information  =---");
  gotoxy(0, 8, 36);
  printf("---=           Enter [Q/q] to quit           =---");
  gotoxy(0, 10, 36);
  printf("=================================================\n");
}

void exitprog() {
  clearConsole();
  gotoxy(10, 9, 31);
  printf("Exiting...");
  gotoxy(0, 11, 36);
  printf("-----------------------------------------------------"
               "------------");
  clearConsole();
}

int getChoice() {
  int choice;
  while (1) {
    scanf("%d", &choice);
    if (choice < 1 || choice > 4) {
      gotoxy(5, 19, 31);
      printf("Invalid choice, please try again: ");
    } else {
      break;
    }
  }
  return choice;
}
