#include "Menu.hpp"
#include "../lib/header.h"
#include "Database.hpp"
#include "VehicleConfiguration.hpp"
#include <chrono>
#include <thread>

void Menu::welcome() {
  clearConsole();
  gotoxy(0, 0, 36); // Cyan color
  std::cout << "-----------------------------------------------------"
               "------------"
            << std::endl;
  std::cout << " __          __    _                               _ "
            << std::endl;
  std::cout << " \\ \\        / /   | |                             | |"
            << std::endl;
  std::cout << "  \\ \\  /\\  / /___ | |  ___  ___   _ __ ___    ___ | |"
            << std::endl;
  std::cout << "   \\ \\/  \\/ // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\| |"
            << std::endl;
  std::cout << "    \\  /\\  /|  __/| || (__| (_) || | | | | ||  __/|_|"
            << std::endl;
  std::cout << "     \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|(_)"
            << std::endl;
  std::cout << "                                                     "
            << std::endl;
  std::cout << "---------------------------------------------------------------"
               "--"
            << std::endl;
  std::cout << std::endl;
}

void Menu::displayMenu() {
  std::cout << "\033[1;33m>>>> MAIN MENU <<<<\033[0m" << std::endl;
  std::cout << "\033[1;32m1.\033[0m Configure a vehicle" << std::endl;
  std::cout << "\033[1;32m2.\033[0m Save Configured vehicle" << std::endl;
  std::cout << "\033[1;31m3.\033[0m Exit" << std::endl;
  std::cout << std::endl;
  std::cout << "\033[1;34mEnter your choice: \033[0m";
}

int Menu::getMenuChoice() {
  int choice;
  std::cin >> choice;
  return choice;
}

void Menu::configCarPrompt() {
  clearConsole();
  gotoxy(0, 2, -1);
  printf("=================================================");
  gotoxy(0, 4, -1);
  printf("---=                 Hello                   =---");
  gotoxy(0, 6, -1);
  printf("---=  Please Enter your Vehicle Information  =---");
  gotoxy(0, 8, -1);
  printf("---=           Enter [Q/q] to quit           =---");
  gotoxy(0, 10, -1);
  printf("=================================================\n");
  getchar();
}

void Menu::exit() {
  std::cout << "\033[1;31mExiting...\033[0m" << std::endl;
  std::cout << std::endl;
  std::cout << "\033[1;36m-----------------------------------------------------"
               "------------\033[0m"
            << std::endl;
  clearConsole();
}
