#ifndef VEHICLECONFIGURATION_HPP
#define VEHICLECONFIGURATION_HPP

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional> // Added header for std::function
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map> // Added header for unordered_map

struct car {
  float carID;
  std::string dealerName, memoReference, color, evOrIc, cargoOrPassenger,
      cargoRoofline, wheelbase, make, model;
  int year, quantity, price;
};

class VehicleConfiguration {
public:
  using Callback = std::function<void()>;
  void setMenuCallback(Callback callback) {
    menuCallback = std::move(callback);
  }
  void run();
  void collectData();
  car getCarData() const { return carData; }

private:
  car carData;
  Callback menuCallback;
  void welcomeMessage();
  std::string inputWithPrompt(const std::string &prompt);
  int inputQuantity();
  std::string setColor(); // Removed parameter
  std::string setEngineType();
  std::string setCargoOrPassenger();
  std::string setCargoRoofline();
  std::string setWheelbase();
  // Added the following method declaration
  std::string
  getOptionFromUser(const std::string &prompt,
                    const std::unordered_map<char, std::string> &options);
  void setCarData(int quantity);
};

#endif // VEHICLECONFIGURATION_HPP
