#include "VehicleConfiguration.hpp"
#include "Database.hpp"

int main() {
  VehicleConfiguration vehicleConfig;
  vehicleConfig.collectData();

  Database dbController;
  dbController.storeVehicleConfiguration(vehicleConfig.getCarData());

  return 0;
}
