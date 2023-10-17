#include "Database.hpp"

Database::Database() {
  /*
  std::filesystem::path dbPath = "./docs";
  if (!std::filesystem::exists(dbPath)) {
      std::filesystem::create_directories(dbPath);
  }
  */

  int rc = sqlite3_open("./docs/database.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    // You might want to handle this error condition.
  }
}

void Database::seedDatabase() {
  // Create the tables and seed the database
  const std::string sql = "CREATE TABLE IF NOT EXISTS vehicle_configuration ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT,"
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
  const char *sql = "INSERT INTO vehicle_configuration ("
                    "vehicle_dealer, vehicle_memo, vehicle_color, "
                    "vehicle_engine, vehicle_cargoOrPassenger, "
                    "vehicle_cargoRoofline, vehicle_wheelbase, vehicle_make, "
                    "vehicle_model, vehicle_year, vehicle_price) VALUES (?, ?, "
                    "?, ?, ?, ?, ?, ?, ?, ?, ?);";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    sqlite3_bind_text(stmt, 1, data.dealerName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, data.memoReference.c_str(), -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, data.color.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, data.evOrIc.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, data.cargoOrPassenger.c_str(), -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, data.cargoRoofline.c_str(), -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 7, data.wheelbase.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 8, data.make.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 9, data.model.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 10, data.year);
    sqlite3_bind_int(stmt, 11, data.price);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Error inserting vehicle_configuration data: "
                << sqlite3_errmsg(db) << std::endl;
    } else {
      std::cout << "Inserted vehicle_configuration data successfully"
                << std::endl;
    }

    sqlite3_finalize(stmt);
  } else {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
  }
}

int Database::viewVehicleConfiguration() {
  const char *sql = "SELECT * FROM vehicle_configuration;";
  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      gotoxy(0, 0, -1);
      printf("============================================\n");
      gotoxy(0, 3, -1);
      std::cout << "ID: " << sqlite3_column_int(stmt, 0) << std::endl;
      std::cout << "Dealer: " << sqlite3_column_text(stmt, 1) << std::endl;
      std::cout << "Memo: " << sqlite3_column_text(stmt, 2) << std::endl;
      std::cout << "Color: " << sqlite3_column_text(stmt, 3) << std::endl;
      std::cout << "Engine: " << sqlite3_column_text(stmt, 4) << std::endl;
      std::cout << "Cargo or Passenger: " << sqlite3_column_text(stmt, 5)
                << std::endl;
      std::cout << "Cargo Roofline: " << sqlite3_column_text(stmt, 6)
                << std::endl;
      std::cout << "Wheelbase: " << sqlite3_column_text(stmt, 7) << std::endl;
      std::cout << "Make: " << sqlite3_column_text(stmt, 8) << std::endl;
      std::cout << "Model: " << sqlite3_column_text(stmt, 9) << std::endl;
      std::cout << "Year: " << sqlite3_column_int(stmt, 10) << std::endl;
      std::cout << "Price: " << sqlite3_column_int(stmt, 11) << std::endl;
      std::cout << std::endl;
      printf("============================================\n");
    }
    sqlite3_finalize(stmt);
    gotoxy(8, 17, 34);
    printf("Press any key to continue...\n");
    getchar();
    while ((getchar()) != '\n');
  } else {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
  }
  return 0;
}

void Database::updateVehicleConfiguration() {}
void Database::deleteVehicleConfiguration() {}

Database::~Database() { sqlite3_close(db); }
