#include "./src/Database.hpp"
#include "./src/Menu.hpp"
#include "./src/VehicleConfiguration.hpp"
#include "./lib/header.h"

int main() {
  Menu menu;
  VehicleConfiguration vehicleConfig;
  Database dbController;

  menu.welcome();
  menu.displayMenu();

  int choice = menu.getMenuChoice();

  switch (choice) {
  case 1:
    clearConsole();
    menu.configCarPrompt();
    vehicleConfig.collectData();
    break;
  case 2:
    menu.exit();
    break;
  case 3:
    dbController.storeVehicleConfiguration(vehicleConfig.getCarData());
    clearConsole();
    break;
  case 4:
    menu.exit();
    break;
  default:
    std::cout << "Invalid choice" << std::endl;
    break;
  }

  return 0;
}
