// @author : Brendan Glancy

#include "VehicleConfiguration.hpp"
#include "../lib/Exceptions.hpp"
#include <sstream>

std::string VehicleConfiguration::input_prompt(const std::string &prompt,
                                                  bool clear) {
  if (clear)
    clear_input_buffer();

  std::cout << prompt;
  std::string input;
  getline(std::cin, input);
  if (input == "q" || input == "Q")
    throw UserQuitException();

  return input;
}

int VehicleConfiguration::input_quantity() {
  std::string input;
  int quantity;

  while (true) {
    input = input_prompt("Enter the quantity of vehicles: ", false);
    std::stringstream ss(input); 
    if (ss >> quantity && ss.eof())
      break;

    std::cout << "Invalid input, please try again." << std::endl;
  }
  return quantity;
}

std::string VehicleConfiguration::get_option(
    const std::string &prompt,
    const std::unordered_map<char, std::string> &options) {

  while (true) {
    char choice = toupper(input_prompt(prompt, false)[0]);

    if (choice == 'Q')
      throw UserQuitException();

    auto found = options.find(choice);
    if (found != options.end()) {
      return found->second; 
    }

    std::cout << "Invalid option. Please try again." << std::endl;
  }
}

// TODO, make this a template function price should be a float
int VehicleConfiguration::get_validated_input(const std::string &prompt) {
  int value;
  std::string input;

  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    std::stringstream ss(input); 
    
    if (ss >> value && ss.eof())
      break;
    std::cout << "Invalid input, please try again." << std::endl;
  }

  return value;
}

std::string VehicleConfiguration::set_color() {
  return get_option("Color (W)hite, (G)ray, (B)lack: ",
                           {
                               {'W', "White"},
                               {'G', "Gray"},
                               {'B', "Black"},
                           });
}

std::string VehicleConfiguration::set_engine() {
  return get_option("Engine Type (EV) or (IC): ", {
                                                             {'E', "EV"},
                                                             {'I', "IC"},
                                                         });
}

std::string VehicleConfiguration::set_cargo_passenger() {
  return get_option("Cargo or Passenger (C)argo or (P)assenger: ",
                           {
                               {'C', "Cargo"},
                               {'P', "Passenger"},
                           });
}

std::string VehicleConfiguration::set_roofline() {
  return get_option("Cargo Roofline (L)ow, (R)aised, (H)igh: ",
                           {
                               {'L', "Low"},
                               {'R', "Raised"},
                               {'H', "High"},
                           });
}

std::string VehicleConfiguration::set_wheelbase() {
  return get_option("Wheelbase (S)hort, (M)edium, (L)ong: ",
                           {
                               {'S', "Short"},
                               {'M', "Medium"},
                               {'L', "Long"},
                           });
}

int VehicleConfiguration::set_price() {
  return get_validated_input("Enter the price of the vehicle(s): ");
}

int VehicleConfiguration::set_year() {
  return get_validated_input("Enter the year of the vehicle(s): ");
}

std::string VehicleConfiguration::set_make() {
  return get_option("Make (T)oyota, (H)onda, (F)ord: ",
                           {
                               {'T', "Toyota"},
                               {'H', "Honda"},
                               {'F', "Ford"},
                           });
}

std::string VehicleConfiguration::set_model(std::string make) {
  if (make == "Toyota") {
    return get_option("Model (C)amry, (R)av4, (P)rius: ",
                             {
                                 {'C', "Camry"},
                                 {'R', "Rav4"},
                                 {'P', "Prius"},
                             });
  } else if (make == "Honda") {
    return get_option("Model (A)ccord, (C)ivic, CR-(V): ",
                             {
                                 {'A', "Accord"},
                                 {'C', "Civic"},
                                 {'V', "Crv"},
                             });
  } else if (make == "Ford") {
    return get_option("Model (F)150, (M)ustang, (E)scape: ",
                             {
                                 {'F', "F150"},
                                 {'M', "Mustang"},
                                 {'E', "Escape"},
                             });
  } else {
    return "Invalid make";
  }
}

void VehicleConfiguration::collect_data() {
  try {
    car_data.dealer_name =
        VehicleConfiguration::input_prompt("Dealer Name: ", true);
    car_data.memo=
        VehicleConfiguration::input_prompt("Memo Reference: ", false);
    car_data.quantity = input_quantity();
    car_data.color = set_color();
    car_data.ev_ic = set_engine();
    car_data.price = set_price();
    car_data.year = set_year();
    car_data.make = set_make();
    car_data.model = set_model(car_data.make);

    if (car_data.ev_ic == "EV") {
      car_data.cargo_passenger = "Cargo";
      car_data.cargo_roofline = "Medium";
      car_data.wheelbase = "Medium";
      return;
    }

    car_data.cargo_passenger = set_cargo_passenger();
    car_data.cargo_roofline = set_roofline();
    car_data.wheelbase = set_wheelbase();
  } catch (const std::exception &e) {
    if (Menu_Callback) {
      Menu_Callback();
    }
  }
}
