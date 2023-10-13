#include "VehicleConfiguration.hpp"
#include "Database.hpp"
#include "Menu.hpp"

int main() {
  Menu menu;
  menu.welcome();

  VehicleConfiguration vehicleConfig;
  vehicleConfig.collectData();

  Database dbController;
  dbController.storeVehicleConfiguration(vehicleConfig.getCarData());

  return 0;
}
