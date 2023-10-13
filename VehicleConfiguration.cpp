#include "VehicleConfiguration.hpp" 
#include "Exceptions.hpp"

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

std::string VehicleConfiguration::getOptionFromUser(
    const std::string& prompt, 
    const std::unordered_map<char, std::string>& options) {
  
    while (true) {
        char choice = toupper(inputWithPrompt(prompt)[0]);
        
        // Check if user wants to quit.
        if (choice == 'Q') {
            throw UserQuitException();
        }

        // Check if choice is valid.
        auto found = options.find(choice);
        if (found != options.end()) {
            return found->second;
        }

        std::cout << "Invalid option. Please try again." << std::endl;
    }
}

std::string VehicleConfiguration::setColor() {
  return getOptionFromUser(
      "Color (W)hite, (G)ray, (B)lack: ",
      {
          {'W', "White"},
          {'G', "Gray"},
          {'B', "Black"},
      });
}

std::string VehicleConfiguration::setEngineType() {
  return getOptionFromUser(
      "Engine Type (EV) or (IC): ",
      {
          {'E', "EV"},
          {'I', "IC"},
      });
}

std::string VehicleConfiguration::setCargoOrPassenger() {
  return getOptionFromUser(
      "Cargo or Passenger (C)argo or (P)assenger: ",
      {
          {'C', "Cargo"},
          {'P', "Passenger"},
      });
}

std::string VehicleConfiguration::setCargoRoofline() {
  return getOptionFromUser(
      "Cargo Roofline (S)hort, (M)edium, (T)all: ",
      {
          {'S', "Short"},
          {'M', "Medium"},
          {'T', "Tall"},
      });
}

std::string VehicleConfiguration::setWheelbase() {
  return getOptionFromUser(
      "Wheelbase (S)hort, (M)edium, (L)ong: ",
      {
          {'S', "Short"},
          {'M', "Medium"},
          {'L', "Long"},
      });
}

// we need to collect the data pass it to our database class to be stored in a database
void VehicleConfiguration::collectData() {
  try {
    carData.dealerName = inputWithPrompt("Dealer Name: ");
    carData.memoReference = inputWithPrompt("Memo Reference: ");
    carData.quantity = inputQuantity();
    carData.color = setColor();
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
  } catch (const UserQuitException&) {
    if (menuCallback) {
      menuCallback();
    }
  }
}

void VehicleConfiguration::setCarData(int quantity) {
  // TODO
}
