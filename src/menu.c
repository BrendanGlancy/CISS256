#include "menu.h"

#include <stdio.h>

#include "../lib/header.h"

void welcome() {
  clear_console();
  gotoxy(0, 0, 34);
  printf("=========================================================");
  gotoxy(2, 2, 36);
  printf(" __          __    _                               _ ");
  gotoxy(2, 3, 36);
  printf(" \\ \\        / /   | |                             | |");
  gotoxy(2, 4, 36);
  printf("  \\ \\  /\\  / /___ | |  ___  ___   _ __ ___    ___ | |");
  gotoxy(2, 5, 36);
  printf("   \\ \\/  \\/ // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\| |");
  gotoxy(2, 6, 36);
  printf("    \\  /\\  /|  __/| || (__| (_) || | | | | ||  __/|_|");
  gotoxy(2, 7, 36);
  printf("     \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|(_)");
  gotoxy(0, 9, 34);
  printf(
      "========================================================="
      "\n");
}

void displayMenu() {
  gotoxy(16, 11, 33);
  printf(">>>> MAIN MENU <<<<");
  gotoxy(16, 13, 32);
  printf("1. Configure a vehicle");
  gotoxy(16, 14, 32);
  printf("2. Save Configured vehicle");
  gotoxy(16, 15, 32);
  printf("3. View Stored Orders");
  gotoxy(16, 16, 32);
  printf("4. Update an Order");
  gotoxy(16, 17, 32);
  printf("5. Delete an Order");
  gotoxy(16, 18, 31);
  printf("6. Exit");
  gotoxy(16, 20, 34);
  printf("Enter your choice: ");
}

void configCarPrompt() {
  clear_console();
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

int getChoice() {
  int choice;
  while (1) {
    scanf("%d", &choice);
    if (choice < 1 || choice > 6) {
      gotoxy(5, 19, 31);
      printf("Invalid choice, please try again: ");
    } else {
      break;
    }
  }
  return choice;
}

// make more dynamic
void infoHeader(char *message) {
  clear_console();
  gotoxy(4, 1, 36);
  printf("=================================================");
  gotoxy(4, 3, 36);
  printf("---=                 Hello                   =---");
  gotoxy(4, 5, 36);
  printf("---=         %s         =---", message);
  gotoxy(4, 7, 36);
  printf("---=            Enter [3] to save            =---");
  gotoxy(4, 9, 36);
  printf("=================================================\n");
}
