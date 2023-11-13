#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "../lib/header.h"

/**
 * @brief The car struct is used to store data collected from the user.
 * @params float x 1
 * @params string x 9
 * @params int x 3
 */
struct Car {
  float id;
  std::string dealer_name, memo, color, ev_ic, cargo_passenger, cargo_roofline,
      wheelbase, make, model = "";

  int year, quantity, price = 0;
};

/**
 * The VehicleConfiguration class is used to collect data from the user and
 * store it in a carData struct.
 */
class VehicleConfiguration {
 public:
  using Callback = std::function<void()>;

  /**
   * Sets a callback function for the menu.
   *
   * @param callback The function to be called for the menu.
   */
  void set_menu_callback(Callback callback) {
    Menu_Callback = std::move(callback);
  }

  /**
   * Runs the menu.
   */
  void run();

  /**
   * Collects data from the user and stores it in the carData struct.
   */
  void collect_data();

  /**
   * Returns the carData struct.
   *
   * @return The carData struct.
   */
  Car get_car_data() const { return car_data; }

 private:
  Car car_data;

  Callback Menu_Callback;
  int input_quantity();

  void welcome_message();
  std::string input_prompt(const std::string &prompt, bool clear);
  std::string set_color();
  std::string set_engine();
  std::string set_cargo_passenger();
  std::string set_roofline();
  std::string set_wheelbase();

  int set_year();
  int set_price();

  std::string set_make();
  std::string set_model(std::string make);
  std::string get_option(const std::string &prompt,
                         const std::unordered_map<char, std::string> &options);

  // TODO, make this a template function price should be a float
  int get_validated_input(const std::string &prompt);
};
