#ifndef MENU_HPP
#define MENU_HPP

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

#endif // VEHICLECONFIGURATION_HPP
