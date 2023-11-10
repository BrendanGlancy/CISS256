#pragma once

#include "header.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Moves the cursor to a specific position in the console and sets the text color.
 * 
 * @param x The x-coordinate (column) of the cursor's new position.
 * @param y The y-coordinate (row) of the cursor's new position.
 * @param color_code The color code for the text. If -1, the color is not changed.
 */
void gotoxy(int x, int y, int color_code) {
  printf("\033[%d;%dH", y, x);
  if (color_code != -1) {
    printf("\033[1;%dm", color_code);
  }
}

void reset_text_color() { printf("\033[0m"); }

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Clears the console screen.
 * 
 * This function uses system-specific commands to clear the console screen.
 * It uses 'cls' for Windows and 'clear' for Unix-based systems.
 */
void clearConsole() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

