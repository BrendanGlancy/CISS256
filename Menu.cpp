#include "Menu.hpp"

void Menu::welcome() {
  std::cout << "\033[1;36m-----------------------------------------------------------------" << std::endl;
  std::cout << "  __          __    _                               _ " << std::endl;
  std::cout << " \\ \\        / /   | |                             | |" << std::endl;
  std::cout << "  \\ \\  /\\  / /___ | |  ___  ___   _ __ ___    ___ | |" << std::endl;
  std::cout << "   \\ \\/  \\/ // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\| |" << std::endl;
  std::cout << "    \\  /\\  /|  __/| || (__| (_) || | | | | ||  __/|_|" << std::endl;
  std::cout << "     \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|(_)" << std::endl;
  std::cout << "                                                     " << std::endl;
  std::cout << "-----------------------------------------------------------------\033[0m" << std::endl;
  std::cout << std::endl;
}

void Menu::displayMenu() {
  std::cout << "\033[1;33m>>>> MAIN MENU <<<<\033[0m" << std::endl;
  std::cout << "\033[1;32m1.\033[0m Configure a vehicle" << std::endl;
  std::cout << "\033[1;32m2.\033[0m Display vehicle configuration" << std::endl;
  std::cout << "\033[1;32m3.\033[0m Save vehicle configuration to file" << std::endl;
  std::cout << "\033[1;31m4.\033[0m Exit" << std::endl;
  std::cout << std::endl;
  std::cout << "\033[1;34mEnter your choice: \033[0m";
}
