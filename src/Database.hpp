#pragma once
#include "VehicleConfiguration.hpp"
#include "../lib/header.h"
#include <sqlite3.h>
#include <filesystem>

class Database {
public:
  // constructor
  Database();

  void connect();
  void seedDatabase();
  void storeVehicleConfiguration(const car &data);
  void viewVehicleConfiguration();

  // destructor
  ~Database();

private:
  sqlite3 *db;
  int genID();
};
