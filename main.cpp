#include "VehicleConfiguration.hpp"
#include "Database.hpp"

int main() {
  VehicleConfiguration vehicleConfig;
  vehicleConfig.collectData();

  Database dbController;
  dbController.storeVehicleConfiguration();

  return 0;
}
