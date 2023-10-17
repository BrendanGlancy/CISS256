#include "./lib/header.h"
#include "./src/menu.h"
#include "./src/Database.hpp"
#include "./src/VehicleConfiguration.hpp"

int main() {
  VehicleConfiguration vehicleConfig;
  Database dbController;

  dbController.seedDatabase();
  welcome();
  int count = 0;
  int carObjCount = 0;

  bool running = true;
  while (running) {
    if (count > 0) infoHeader(carObjCount);
    displayMenu();

    int choice = getChoice();
    count++;

    switch (choice) {
    case 1: // Collect data
      carObjCount++;
      clearConsole();
      configCarPrompt();
      vehicleConfig.collectData();
      break;
    case 2: // Store data
      dbController.storeVehicleConfiguration(vehicleConfig.getCarData());
      break;
    case 3: // View data
      clearConsole();
      dbController.viewVehicleConfiguration();
      clearConsole();
      break;
    case 4: // Exit program
      clearConsole();
      running = false;
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
      break;
    }
  }

  return 0;
}
