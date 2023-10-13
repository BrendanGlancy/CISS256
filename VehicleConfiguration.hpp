#ifndef VEHICLECONFIGURATION_HPP
#define VEHICLECONFIGURATION_HPP

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <limits>
#include <fstream>

// Declaration of the 'car' struct
struct car {
    float carID;
    std::string dealerName, memoReference, color, evOrIc, cargoOrPassenger, cargoRoofline, wheelbase;
    int year, quantity;
};

// Declaration of the 'VehicleConfiguration' class
class VehicleConfiguration {
public:
    void run();

private:
    car carData;

    void welcomeMessage();
    std::string inputWithPrompt(const std::string& prompt);
    int inputQuantity();
    std::string setColor(std::string prompt);
    std::string setEngineType();
    std::string setCargoOrPassenger();
    std::string setCargoRoofline();
    std::string setWheelbase();
    void setCarData(int quantity);
    void collectData();
    car getCarData() const { return carData; }
};

#endif // VEHICLECONFIGURATION_HPP
