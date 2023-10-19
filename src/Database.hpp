#pragma once
#include "../lib/header.h"
#include "VehicleConfiguration.hpp"
#include <filesystem>
#include <sqlite3.h>

class Database {
public:
  // constructor
  Database();

  void connect();
  void seed_db();

  void insert_db(const car &data); // create
  void query_all();                  
  void update_db();               // update
  void delete_db();               // delete
  
  int get_id();

  // destructor
  ~Database();

private:
  sqlite3 *db;
  void display_db(sqlite3_stmt *stmt);  
  void sql_error(sqlite3_stmt *stmt, std::string msg);
};
