#pragma once

#include <iostream>
#include <string>

class Menu {
public:
  void welcome();
  void displayMenu();
  void configureMenu();
  int getMenuChoice();
  void configCarPrompt();
  void exit();
};
