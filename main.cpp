#include "./lib/header.h"
#include "./src/Database.hpp"
#include "./src/Menu.hpp"
#include "./src/VehicleConfiguration.hpp"

void clearUp() {}

int main() {
  Menu menu;
  VehicleConfiguration vehicleConfig;
  Database dbController;

  menu.welcome();

  bool running = true;
  while (running) {
    menu.displayMenu();
    int choice = menu.getMenuChoice();

    switch (choice) {
    case 1: // Collect data
      clearConsole();
      menu.configCarPrompt();
      vehicleConfig.collectData();
      break;
    case 2: // Store data
      clearConsole();
      dbController.storeVehicleConfiguration(vehicleConfig.getCarData());
      break;
    case 3: // Exit program
      menu.exit();
      running = false;
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
      break;
    }
  }

  return 0;
}
