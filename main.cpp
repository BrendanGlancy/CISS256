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
  char *message = (char*)malloc(50);

  bool running = true;
  while (running) {
    if (count > 0) infoHeader(message);
    displayMenu();

    int choice = getChoice();
    count++;

    switch (choice) {
    case 1: // Collect data
      carObjCount++;
      clearConsole();
      sprintf(message, "%d car object(s) created", carObjCount);;
      configCarPrompt();
      vehicleConfig.collectData();
      break;
    case 2: // Store data
      dbController.storeVehicleConfiguration(vehicleConfig.getCarData());
      strcpy(message, "   Save data success   ");
      break;
    case 3: // View data
      clearConsole();
      dbController.viewVehicleConfiguration();
      strcpy(message, "   View data success   ");
      clearConsole();
      break;
    case 4:
      strcpy(message, "  Not yet implemented  ");
      break;
    case 5:
      strcpy(message, "  Not yet implemented  ");
      break;
    case 6: // Exit program
      clearConsole();
      running = false;
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
      break;
    }
  }

  free(message);
  return 0;
}
