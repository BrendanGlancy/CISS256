#include "./lib/header.h"
#include "./src/Database.hpp"
#include "./src/VehicleConfiguration.hpp"
#include "./src/menu.h"
#include <vector>

void handleCollectData(std::vector<VehicleConfiguration *> &vehicleConfigs,
                       char *message, int &carObjCount) {
  vehicleConfigs.push_back(new VehicleConfiguration());
  carObjCount++;
  clearConsole();
  sprintf(message, "%d car object(s) created", carObjCount);
  configCarPrompt();
  vehicleConfigs.back()->collectData();
}

void handleStoreData(Database &dbController,
                     std::vector<VehicleConfiguration *> &vehicleConfigs,
                     char *message) {
    if (!vehicleConfigs.empty()) {
        for (auto vehicleConfig : vehicleConfigs) {
            dbController.insert_db(vehicleConfig->getCarData());
            delete vehicleConfig; // delete the object to prevent memory leak
        }
        vehicleConfigs.clear(); // clear the vector
        strcpy(message, "  Data save success   ");
    } else {
        strcpy(message, "   No data to save     ");
    }
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

void handleUpdateData(Database &dbController, char *message) {
  clearConsole();
  dbController.query_all();
  dbController.update_db();
  strcpy(message, "  Update data success  ");
}

int main() {
  int count = 0;
  int carObjCount = 0;
  char *message = (char *)malloc(sizeof("  Delete data success  ") + 2);

  bool running = true;

  std::vector<VehicleConfiguration *> vehicleConfigs;
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
      handleCollectData(vehicleConfigs, message, carObjCount);
      break;
    case 2:
      handleStoreData(dbController, vehicleConfigs, message);
      break;
    case 3:
      handleViewData(dbController, message);
      break;
    case 4:
      handleUpdateData(dbController, message);
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
