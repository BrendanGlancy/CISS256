#include "VehicleConfiguration.hpp"
#include "../lib/Exceptions.hpp"

// Path: VehicleConfiguration.cpp

std::string VehicleConfiguration::inputWithPrompt(const std::string &prompt,
                                                  bool clear) {
  if (clear)
    clearInputBuffer();

  std::cout << prompt;
  std::string input;
  getline(std::cin, input);
  if (input == "q" || input == "Q")
    throw UserQuitException();

  return input;
}

int VehicleConfiguration::inputQuantity() {
  std::string input;
  int quantity;

  while (true) {
    input = inputWithPrompt("Enter the quantity of vehicles: ", false);
    std::stringstream ss(input);
    if (ss >> quantity && ss.eof())
      break;

    std::cout << "Invalid input, please try again." << std::endl;
  }
  return quantity;
}

std::string VehicleConfiguration::getOptionFromUser(
    const std::string &prompt,
    const std::unordered_map<char, std::string> &options) {

  while (true) {
    char choice = toupper(inputWithPrompt(prompt, false)[0]);

    // Check if user wants to quit.
    if (choice == 'Q')
      throw UserQuitException();

    // Check if choice is valid.
    auto found = options.find(choice);
    if (found != options.end()) {
      return found->second;
    }

    std::cout << "Invalid option. Please try again." << std::endl;
  }
}

// TODO, make this a template function price should be a float
int VehicleConfiguration::getValidatedInput(const std::string &prompt) {
  int value;
  std::string input;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    std::stringstream ss(input);
    if (ss >> value && ss.eof()) {
      break;
    }
    std::cout << "Invalid input, please try again." << std::endl;
  }

  return value;
}

std::string VehicleConfiguration::setColor() {
  return getOptionFromUser("Color (W)hite, (G)ray, (B)lack: ",
                           {
                               {'W', "White"},
                               {'G', "Gray"},
                               {'B', "Black"},
                           });
}

std::string VehicleConfiguration::setEngineType() {
  return getOptionFromUser("Engine Type (EV) or (IC): ", {
                                                             {'E', "EV"},
                                                             {'I', "IC"},
                                                         });
}

std::string VehicleConfiguration::setCargoOrPassenger() {
  return getOptionFromUser("Cargo or Passenger (C)argo or (P)assenger: ",
                           {
                               {'C', "Cargo"},
                               {'P', "Passenger"},
                           });
}

std::string VehicleConfiguration::setCargoRoofline() {
  return getOptionFromUser("Cargo Roofline (L)ow, (R)aised, (H)igh: ",
                           {
                               {'L', "Low"},
                               {'R', "Raised"},
                               {'H', "High"},
                           });
}

std::string VehicleConfiguration::setWheelbase() {
  return getOptionFromUser("Wheelbase (S)hort, (M)edium, (L)ong: ",
                           {
                               {'S', "Short"},
                               {'M', "Medium"},
                               {'L', "Long"},
                           });
}

int VehicleConfiguration::setPrice() {
  return getValidatedInput("Enter the price of the vehicle(s): ");
}

int VehicleConfiguration::setYear() {
  return getValidatedInput("Enter the year of the vehicle(s): ");
}

std::string VehicleConfiguration::setMake() {
  return getOptionFromUser("Make (T)oyota, (H)onda, (F)ord: ",
                           {
                               {'T', "Toyota"},
                               {'H', "Honda"},
                               {'F', "Ford"},
                           });
}

std::string VehicleConfiguration::setModel(std::string make) {
  if (make == "Toyota") {
    return getOptionFromUser("Model (C)amry, (R)av4, (P)rius: ",
                             {
                                 {'C', "Camry"},
                                 {'R', "Rav4"},
                                 {'P', "Prius"},
                             });
  } else if (make == "Honda") {
    return getOptionFromUser("Model (A)ccord, (C)ivic, CR-(V): ",
                             {
                                 {'A', "Accord"},
                                 {'C', "Civic"},
                                 {'V', "Crv"},
                             });
  } else if (make == "Ford") {
    return getOptionFromUser("Model (F)150, (M)ustang, (E)scape: ",
                             {
                                 {'F', "F150"},
                                 {'M', "Mustang"},
                                 {'E', "Escape"},
                             });
  } else {
    return "Invalid make";
  }
}

// we need to collect the data pass it to our database class to be stored in a
// database
void VehicleConfiguration::collectData() {
  try {
    carData.dealerName =
        VehicleConfiguration::inputWithPrompt("Dealer Name: ", true);
    carData.memoReference =
        VehicleConfiguration::inputWithPrompt("Memo Reference: ", false);
    carData.quantity = inputQuantity();
    carData.color = setColor();
    carData.evOrIc = setEngineType();
    carData.price = setPrice();
    carData.year = setYear();
    carData.make = setMake();
    carData.model = setModel(carData.make);
    if (carData.evOrIc == "EV") {
      carData.cargoOrPassenger = "Cargo";
      carData.cargoRoofline = "Medium";
      carData.wheelbase = "Medium";
    }
    carData.cargoOrPassenger = setCargoOrPassenger();
    carData.cargoRoofline = setCargoRoofline();
    carData.wheelbase = setWheelbase();
  } catch (const std::exception &e) {
    if (menuCallback) {
      menuCallback();
    }
  }
}
