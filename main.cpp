#include "./lib/header.h"
#include "./src/Database.hpp"
#include "./src/VehicleConfiguration.hpp"
#include "./src/menu.h"

void handleCollectData(VehicleConfiguration &vehicleConfig, char *message,
                       int &carObjCount) {
  carObjCount++;
  clearConsole();
  sprintf(message, "%d car object(s) created", carObjCount);
  configCarPrompt();
  vehicleConfig.collectData();
}

void handleStoreData(Database &dbController,
                     VehicleConfiguration &vehicleConfig, char *message) {
  dbController.insert_db(vehicleConfig.getCarData());
  strcpy(message, "   Save data success   ");
}

void handleViewData(Database &dbController, char *message) {
  clearConsole();
  dbController.query_all();
  strcpy(message, "   View data success   ");
  clearConsole();
}

void handleDeleteData(Database &dbController, char *message) {
  clearConsole();
  dbController.query_all();
  dbController.delete_db();
  strcpy(message, "  Delete data success  ");
}

int main() {
  int count = 0;
  int carObjCount = 0;
  char *message = (char *)malloc(50);
  bool running = true;

  VehicleConfiguration vehicleConfig;
  Database dbController;

  dbController.seed_db();
  welcome();

  while (running) {
    if (count > 0)
      infoHeader(message);
    displayMenu();

    int choice = getChoice();
    count++;

    switch (choice) {
    case 1:
      handleCollectData(vehicleConfig, message, carObjCount);
      break;
    case 2:
      handleStoreData(dbController, vehicleConfig, message);
      break;
    case 3:
      handleViewData(dbController, message);
      break;
    case 4:
      strcpy(message, "  Not yet implemented  ");
      break;
    case 5:
      handleDeleteData(dbController, message);
      break;
    case 6:
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
