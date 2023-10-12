#include "Menu.hpp"

void Menu::welcome() {
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << "  __          __    _                               _ " << std::endl;
    std::cout << " \\ \\        / /   | |                             | |" << std::endl;
    std::cout << "  \\ \\  /\\  / /___ | |  ___  ___   _ __ ___    ___ | |" << std::endl;
    std::cout << "   \\ \\/  \\/ // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\| |" << std::endl;
    std::cout << "    \\  /\\  /|  __/| || (__| (_) || | | | | ||  __/|_|" << std::endl;
    std::cout << "     \\/  \\/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|(_)" << std::endl;
    std::cout << "                                                     " << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;
    std::cout << std::endl;
}

void Menu::displayMenu() {
    welcome();
    std::cout << "1. Configure a vehicle" << std::endl;
    std::cout << "2. Display vehicle configuration" << std::endl;
    std::cout << "3. Save vehicle configuration to file" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter your choice: ";
}
