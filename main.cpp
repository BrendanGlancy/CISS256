#include "Database.hpp"
#include "Menu.hpp"
#include "VehicleConfiguration.hpp"

int main() {
  // obj init
  Menu menu;
  VehicleConfiguration vehicleConfig;
  Database dbController;

  menu.welcome();
  menu.displayMenu();

  int choice = menu.getMenuChoice();

  switch (choice) {
  case 1:
    vehicleConfig.collectData();
    break;
  case 2:
    menu.exit();
    break;
  case 3:
    dbController.storeVehicleConfiguration(vehicleConfig.getCarData());
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
