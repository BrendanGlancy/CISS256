#pragma once
#include "../lib/header.h"
#include "VehicleConfiguration.hpp"
#include <filesystem>
#include <sqlite3.h>

class Database {
public:
  // constructor
  Database();

  void seed_db();
  void insert_db(const car &data); // create

  void query_all(); // read
  void update_db(); // update
  void delete_db(); // delete

  // testing
  bool table_exists(const std::string &table_name);
  bool column_exists(const std::string &table_name,
                     const std::string &column_name);

  // destructor
  ~Database();

private:
  sqlite3 *db;
  void connect();
  void display_db(sqlite3_stmt *stmt);
  void sql_error(sqlite3_stmt *stmt, std::string msg);
  void execute_sql(const std::string &sql, const std::string &msg);
  bool prepare_stmt(const char *sql, sqlite3_stmt **stmt);
  std::string col_choice();
  std::string get_update();
  void bind_stmt(sqlite3_stmt *stmt, const car &data);
  int get_id();
};
