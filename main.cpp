#include "VehicleConfiguration.hpp"
#include "Database.hpp"
#include "Menu.hpp"

int main() {
  // obj init
  Menu menu;
  VehicleConfiguration vehicleConfig;

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
      menu.exit();
      break;
    case 4:
      menu.exit();
      break;
    default:
      std::cout << "Invalid choice" << std::endl;
      break;
  }

  Database dbController;
  dbController.storeVehicleConfiguration(vehicleConfig.getCarData());

  return 0;
}
