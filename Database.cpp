#include "Database.hpp"
// Include necessary libraries for database operations...

sqlite3 *db;

void Database::connect() {
  int rc = sqlite3_open("database.db", &db);
  if (rc) {
    std::cout << "Can't open database: " << std::endl;
  } else {
    std::cout << "Opened database successfully" << std::endl;
  }
}

void Database::seedDatabase() {
  // create the tables and seed the database
  std::string sql = "CREATE TABLE IF NOT EXISTS vehicle_configuration ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "vehicle_id TEXT NOT NULL,"
                    "vehicle_color TEXT NOT NULL,"
                    "vehicle_year INTEGER NOT NULL,"
                    "vehicle_engine TEXT NOT NULL,"
                    "vehicle_make TEXT NOT NULL,"
                    "vehicle_model TEXT NOT NULL,"
                    "vehicle_price INTEGER NOT NULL);";
  int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
  if (rc != SQLITE_OK) {
    std::cout << "Error creating vehicle_configuration table" << std::endl;
  } else {
    std::cout << "Created vehicle_configuration table successfully"
              << std::endl;
  }
}

void Database::storeVehicleConfiguration(const car &data) {}
