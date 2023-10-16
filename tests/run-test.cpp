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
  // and has the expected structure. For now, just illustrating the setup.
}

int main() {
  testDatabaseConstructor();
  return 0;
}
