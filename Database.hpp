#pragma once
#include "VehicleConfiguration.hpp"
#include <sqlite3.h>

class Database {
public:
  void connect();
  void seedDatabase();
  void storeVehicleConfiguration(const car &data);
};
