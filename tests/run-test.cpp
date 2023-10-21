#include "../lib/header.h"
#include "../src/Database.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>

void testDatabaseConstructor() {
  Database db;

  // Test 1: Ensure the database file is created.
  if (std::filesystem::exists("./docs/database.db")) {
    printf("Test 1 passed ✅ \n");
  }

  // Test 2 and 3 can involve querying the database to ensure the table exists
  if (db.table_exists("vehicle_configuration")) {
    printf("Test 2 passed ✅ \n");
  }

  // Test 3: Ensure the table has the correct columns.
  // if (db.column_exists("vehicle_configuration", "id") &&
  //     db.column_exists("vehicle_configuration", "make") &&
  //     db.column_exists("vehicle_configuration", "model") &&
  //     db.column_exists("vehicle_configuration", "year") &&
  //     db.column_exists("vehicle_configuration", "color") &&
  //     db.column_exists("vehicle_configuration", "engine") &&
  //     db.column_exists("vehicle_configuration", "transmission") &&
  //     db.column_exists("vehicle_configuration", "drive_type") &&
  //     db.column_exists("vehicle_configuration", "fuel_type") &&
  //     db.column_exists("vehicle_configuration", "body_style") &&
  //     db.column_exists("vehicle_configuration", "doors") &&
  //     db.column_exists("vehicle_configuration", "seats") &&
  //     db.column_exists("vehicle_configuration", "price")) {
  //   printf("Test 3 passed ✅ \n");
  // }
}

int main() {
  testDatabaseConstructor();
  return 0;
}
