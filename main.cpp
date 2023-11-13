#include <vector>

#include "./lib/header.h"
#include "./src/Database.hpp"
#include "./src/VehicleConfiguration.hpp"
#include "./src/menu.h"

/**
 * Technically you can buffer overflow the message variable
 * Would be kinda fun to try because you would have to make a lot of car
 * objects
 */
void handleCollectData(std::vector<VehicleConfiguration *> &vehicle_configs,
                       char *message, int &car_objs) {
  vehicle_configs.push_back(new VehicleConfiguration());
  // you dont actually need to keep track of these anymore
  car_objs = vehicle_configs.size();
  clear_console();
  snprintf(message, sizeof("   Data save success   "),
           "%d car object(s) created", car_objs);
  configCarPrompt();
  vehicle_configs.back()->collect_data();
}

void handleStoreData(Database &db_controller,
                     std::vector<VehicleConfiguration *> &vehicle_configs,
                     char *message) {
  if (!vehicle_configs.empty()) {
    for (auto vehicleConfig : vehicle_configs) {
      db_controller.insert_db(vehicleConfig->get_car_data());
      delete vehicleConfig;
    }
    vehicle_configs.clear();
    strcpy(message, "   Data save success   ");
  } else {
    strcpy(message, "   No data to save     ");
  }
}

void handleViewData(Database &db_controller, char *message) {
  clear_console();
  db_controller.query_all();
  strcpy(message, "   View data success   ");
  clear_console();
}

void handleDeleteData(Database &db_controller, char *message) {
  clear_console();
  db_controller.query_all();
  db_controller.delete_db();
  strcpy(message, "  Delete data success  ");
}

void handleUpdateData(Database &db_controller, char *message) {
  clear_console();
  db_controller.query_all();
  db_controller.update_db();
  strcpy(message, "  Update data success  ");
}

int main() {
  int count = 0;
  int car_objs = 0;
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
      handleCollectData(vehicle_configs, message, car_objs);
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
      clear_console();
      reset_text_color();
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
