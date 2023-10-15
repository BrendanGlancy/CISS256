#pragma once
#include "VehicleConfiguration.hpp"
#include <sqlite3.h>

class Database {
public:
  // constructor
  Database();

  void connect();
  void seedDatabase();
  void storeVehicleConfiguration(const car &data);

  // destructor
  ~Database();

private:
  sqlite3 *db;
};
