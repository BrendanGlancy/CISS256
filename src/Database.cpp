#include "Database.hpp"

Database::Database() {
  int rc = sqlite3_open("../docs/database.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    // You might want to handle this error condition.
  } else {
    std::cout << "Opened database successfully" << std::endl;
  }
}

void Database::seedDatabase() {
  // Create the tables and seed the database
  const std::string sql = "CREATE TABLE IF NOT EXISTS vehicle_configuration ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "vehicle_id TEXT NOT NULL,"
                          "vehicle_dealer TEXT NOT NULL,"
                          "vehicle_memo TEXT NOT NULL,"
                          "vehicle_color TEXT NOT NULL,"
                          "vehicle_engine TEXT NOT NULL,"
                          "vehicle_cargoOrPassenger TEXT NOT NULL,"
                          "vehicle_cargoRoofline TEXT NOT NULL,"
                          "vehicle_wheelbase TEXT NOT NULL,"
                          "vehicle_make TEXT NOT NULL,"
                          "vehicle_model TEXT NOT NULL,"
                          "vehicle_year INTEGER NOT NULL,"
                          "vehicle_price INTEGER NOT NULL);";

  char *errMsg = nullptr;
  int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error creating vehicle_configuration table: " << errMsg
              << std::endl;
    sqlite3_free(errMsg);
    // You might want to handle this error condition.
  } else {
    std::cout << "Created vehicle_configuration table successfully"
              << std::endl;
  }
}

void Database::storeVehicleConfiguration(const car &data) {
  std::string sql = "INSERT INTO vehicle_configuration (vehicle_id, "
                    "vehicle_dealer, vehicle_memo, vehicle_color, "
                    "vehicle_engine, vehicle_cargoOrPassenger, "
                    "vehicle_cargoRoofline, vehicle_wheelbase, vehicle_make, "
                    "vehicle_model, vehicle_year, vehicle_price) VALUES (";

  char *errMsg = nullptr;
  int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error inserting vehicle_configuration data: " << errMsg
              << std::endl;
    sqlite3_free(errMsg);
    // You might want to handle this error condition.
  } else {
    std::cout << "Inserted vehicle_configuration data successfully"
              << std::endl;
  }
}

Database::~Database() { sqlite3_close(db); }
