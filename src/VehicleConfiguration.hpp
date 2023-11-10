#pragma once

#include "../lib/header.h"
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

/**
 * @brief The car struct is used to store data collected from the user.
 * @params float x 1
 * @params string x 9
 * @params int x 3
 */
struct Car {
  float id;
  std::string dealerName, memoReference, color, evOrIc, cargoOrPassenger,
      cargoRoofline, wheelbase, make, model = "";

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
  void setMenuCallback(Callback callback) {
    menuCallback = std::move(callback);
  }

  /**
   * Runs the menu.
   */
  void run();

  /**
   * Collects data from the user and stores it in the carData struct.
   */
  void collectData();

  /**
   * Returns the carData struct.
   *
   * @return The carData struct.
   */
  Car getCarData() const { return carData; }

private:
  // declare the carData struct as a pointer
  Car carData;

  Callback menuCallback;
  int inputQuantity();

  void welcomeMessage();
  std::string inputWithPrompt(const std::string &prompt, bool clear);
  std::string setColor();
  std::string setEngineType();
  std::string setCargoOrPassenger();
  std::string setCargoRoofline();
  std::string setWheelbase();
  int setYear();
  int setPrice();
  std::string setMake();
  std::string setModel(std::string make);
  std::string
  getOptionFromUser(const std::string &prompt,
                    const std::unordered_map<char, std::string> &options);
  int getValidatedInput(const std::string &prompt);
};
