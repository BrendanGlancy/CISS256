#include "./lib/header.h"
#include "./src/Database.hpp"
#include "./src/VehicleConfiguration.hpp"
#include "./src/menu.h"
#include <vector>

/**
 * @note The car object is stored in the vector as a pointer
 * To avoid copying the object when pushing it to the vector
 */
void handleCollectData(std::vector<VehicleConfiguration *> &vehicle_configs,
                       char *message, int &carObjCount) {
  vehicle_configs.push_back(new VehicleConfiguration());
  carObjCount++;
  clearConsole();
  printf(message, "%d car object(s) created", carObjCount);
  configCarPrompt();
  vehicle_configs.back()->collectData(); // collect data for the last car object
}

void handleStoreData(Database &db_controller,
                     std::vector<VehicleConfiguration *> &vehicle_configs,
                     char *message) {
  if (!vehicle_configs.empty()) {
    /**
     * NOTE according to google cpp style guide
     * Use type deduction only if it makes the code clearer to readers who
     * aren't familiar with the project, or if it makes the code safer. Do not
     * use it merely to avoid the inconvenience of writing an explicit type. NOT
     * sure how else this could be done
     */
    for (auto vehicleConfig : vehicle_configs) {
      db_controller.insert_db(vehicleConfig->getCarData());
      delete vehicleConfig; // delete the object to prevent memory leak
    }
    vehicle_configs.clear(); // clear the vector
    strcpy(message, "  Data save success   ");
  } else {
    strcpy(message, "   No data to save     ");
  }
}

void handleViewData(Database &db_controller, char *message) {
  clearConsole();
  db_controller.query_all();
  strcpy(message, "   View data success   ");
  clearConsole();
}

void handleDeleteData(Database &db_controller, char *message) {
  clearConsole();
  db_controller.query_all();
  db_controller.delete_db();
  strcpy(message, "  Delete data success  ");
}

void handleUpdateData(Database &db_controller, char *message) {
  clearConsole();
  db_controller.query_all();
  db_controller.update_db();
  strcpy(message, "  Update data success  ");
}

int main() {
  int count = 0;
  int carObjCount = 0;
  char *message = (char *)malloc(sizeof("  Delete data success  ") + 2);

  bool running = true;

  std::vector<VehicleConfiguration *> vehicle_configs;
  Database db_controller;

  db_controller.seed_db();
  welcome();

  while (running) {
    if (count > 0)
      infoHeader(message);
    displayMenu();

    int choice = getChoice();
    count++;

    switch (choice) {
    case 1:
      handleCollectData(vehicle_configs, message, carObjCount);
      break;
    case 2:
      handleStoreData(db_controller, vehicle_configs, message);
      break;
    case 3:
      handleViewData(db_controller, message);
      break;
    case 4:
      handleUpdateData(db_controller, message);
      break;
    case 5:
      handleDeleteData(db_controller, message);
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
