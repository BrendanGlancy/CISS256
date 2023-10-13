#include "VehicleConfiguration.hpp" 
#include "Exceptions.hpp"
#include <cctype>
#include <cstdlib>

// Path: VehicleConfiguration.cpp

std::string VehicleConfiguration::inputWithPrompt(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    getline(std::cin, input);
    return input;
}

int VehicleConfiguration::inputQuantity() {
    std::string input;
    int quantity;
    while (true) {
        input = inputWithPrompt("Enter the quantity of vehicles: ");
        std::stringstream ss(input);
        if (ss >> quantity) {
            if (ss.eof()) {
                break;
            }
        }
        std::cout << "Invalid input, please try again." << std::endl;
    }
    return quantity;
}

std::string VehicleConfiguration::setColor(std::string prompt) {
    char choice = toupper(prompt[0]);
    switch (choice) {
      case 'W': return "White";
      case 'G': return "Grey";
      case 'B': return "Black";
      case 'Q': throw UserQuitException();
      default: throw std::runtime_error("Error reading color");
    }
}

std::string VehicleConfiguration::setEngineType() {
    do {
      auto type = inputWithPrompt("EV or IC: ");
      type = toupper(type[0]);
      if (type == "E" || type == "EV") return "EV";
      if (type == "I" || type == "IC") return "IC";
      if (type == "Q") throw UserQuitException();
    } while (true);
}

std::string VehicleConfiguration::setCargoOrPassenger() {
  while (true) {
    char choice = toupper(inputWithPrompt("(C)argo or (P)assenger: ")[0]);
    switch (choice) {
        case 'C': return "Cargo";
        case 'P': return "Passenger";
        case 'Q': throw UserQuitException();
        default: throw std::runtime_error("Error reading cargo or passenger type");
    }
  }
}
std::string VehicleConfiguration::setCargoRoofline() {
  while (true) {
    char choice = toupper(inputWithPrompt("Cargo Roofline (L)ow, (R)aised, (H)igh: ")[0]);
    switch (choice) {
        case 'L': return "Low";
        case 'R': return "Raised";
        case 'H': return "High";
        case 'Q': throw UserQuitException();
        default: throw std::runtime_error("Error reading cargo roofline");
    }
  }
}

std::string VehicleConfiguration::setWheelbase() {
  while (true) {
    char choice = toupper(inputWithPrompt("Wheelbase (S)hort, (M)edium, (E)xtended: ")[0]);
    switch (choice) {
        case 'S': return "Short";
        case 'M': return "Medium";
        case 'E': return "Extended";
        case 'Q': throw UserQuitException();
        default: throw std::runtime_error("Error reading wheelbase");
    }
  }
}

// we need to collect the data pass it to our database class to be stored in a database
void VehicleConfiguration::collectData() {
  try {
    carData.dealerName = inputWithPrompt("Dealer Name: ");
    carData.memoReference = inputWithPrompt("Memo Reference: ");
    carData.quantity = inputQuantity();
    carData.color = setColor(inputWithPrompt("Color (W)hite, (G)ray, (B)lack: "));
    carData.evOrIc = setEngineType();
    setCarData(carData.quantity);
    if (carData.evOrIc != "EV") {
      carData.cargoOrPassenger = setCargoOrPassenger();
      carData.cargoRoofline = setCargoRoofline();
      carData.wheelbase = setWheelbase();
    } else if (carData.evOrIc == "EV") {
      carData.cargoOrPassenger = "Cargo";
      carData.cargoRoofline = "Medium";
      carData.wheelbase = "Medium";
    }
  } catch (const UserQuitException& e) {
    if (menuCallback) {
      menuCallback();
    }
  }
}

void VehicleConfiguration::setCarData(int quantity) {
  // TODO
}
