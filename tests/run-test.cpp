#include "../lib/header.h"
#include "../src/Database.hpp"
#include <cassert>
#include <filesystem>
#include <iostream>

void testDatabaseConstructor() {
  Database db;

  // Test 1: Ensure the database file is created.
  assert(std::filesystem::exists("./docs/database.db"));
  db.seedDatabase();

  // Test 2 and 3 can involve querying the database to ensure the table exists
  // and has the expected structure. For now, just illustrating the setup.
}

int main() {
  testDatabaseConstructor();
  return 0;
}
