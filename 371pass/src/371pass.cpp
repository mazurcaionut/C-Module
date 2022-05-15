// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include "371pass.h"
#include "lib_cxxopts.hpp"
#include "wallet.h"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a Wallet object
//  2. Parse the 'action' argument to decide what action should be taken (
//     create, read, update, or delete). Read is the easiest to implement, and
//     update is the hardest. The details of how these arguments work is in the
//     coursework specification.
//  4. Save the updated Wallet object to the JSON file if there have been
//     changes (calling save() on the Wallet object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[]) {
  auto options = App::cxxoptsSetup();
  auto args = options.parse(argc, argv);

  // Print the help usage if requested
  if (args.count("help")) {
    std::cout << options.help() << '\n';
    return 0;
  }

  // Open the database and construct the Wallet
  const std::string db = args["db"].as<std::string>();
  Wallet wObj{};
  // Only uncomment this once you have implemented the load function!
  wObj.load(db);

  try {

  const Action a = parseActionArgument(args);
  switch (a) {
  case Action::CREATE: {
    try{
      std::string category = args.count("category") ? args["category"].as<std::string>() : "";
      std::string item = args.count("item") ? args["item"].as<std::string>() : "";
      std::string entry = args.count("entry") ? args["entry"].as<std::string>() : "";

      if(category.empty() && item.empty() && entry.empty()) {
        std::cerr<< "Error: missing category, item or entry argument(s).\n";
        std::exit(1);
      } else if(!category.empty() && item.empty() && entry.empty()) {

        wObj.newCategory(category);
        wObj.save(db);

      } else if(!category.empty() && !item.empty() && entry.empty()) {
        wObj.newCategory(category).newItem(item);
        wObj.save(db);

      } else {
        std::string delimiter = ",";

      if(entry.find(delimiter) != std::string::npos) {

        std::string key = entry.substr(0, entry.find(delimiter));
        std::string value = entry.substr(entry.find(delimiter) + 1, entry.size());


        wObj.newCategory(category).newItem(item).addEntry(key, value);
        wObj.save(db);
        }
      }  
      break;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    };
  }
  case Action::READ:{
    try {
    std::string category = args.count("category") ? args["category"].as<std::string>() : "";
    std::string item = args.count("item") ? args["item"].as<std::string>() : "";
    std::string entry = args.count("entry") ? args["entry"].as<std::string>() : "";

    if(category.empty() && item.empty() && entry.empty()) {
      std::cout << getJSON(wObj) << std::endl;
    } else if (!category.empty() && item.empty() && entry.empty()) {
      std::cout << getJSON(wObj, category) << std::endl;
    } else if(!category.empty() && !item.empty() && entry.empty()) {
      std::cout << getJSON(wObj, category, item) << std::endl;
    } else {
      std::cout << getJSON(wObj, category, item, entry) << std::endl;
    }
     
    break;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    };

  }
  case Action::UPDATE:{
    try {
      std::string category = args.count("category") ? args["category"].as<std::string>() : "";
      std::string item = args.count("item") ? args["item"].as<std::string>() : "";
      std::string entry = args.count("entry") ? args["entry"].as<std::string>() : "";


      if(!category.empty() && item.empty() && entry.empty()) {
        std::string delimiter = ":";

        if(category.find(delimiter) != std::string::npos) {

          std::string oldIdentifier = category.substr(0, category.find(delimiter));
          std::string newIdentifier = category.substr(category.find(delimiter) + 1, category.size());

          wObj.getCategory(oldIdentifier).setIdent(newIdentifier);
          wObj.save(db);
        } else {
          std::cerr<< "Error: Invalid delimiter\n";
          std::exit(1);
        }
      } else if(!category.empty() && !item.empty() && entry.empty()) {

          std::string delimiter = ":";

          if(item.find(delimiter) != std::string::npos) {

            std::string oldIdentifier = item.substr(0, item.find(delimiter));
            std::string newIdentifier = item.substr(item.find(delimiter) + 1, item.size());

            wObj.getCategory(category).getItem(oldIdentifier).setIdent(newIdentifier);
            wObj.save(db);
          } else {
            std::cerr<< "Error: Invalid delimiter\n";
            std::exit(1);
          }
      } else {
          std::string comaDelimiter = ",";
          std::string colonDelimiter = ":";

          if(entry.find(colonDelimiter) != std::string::npos && entry.find(comaDelimiter) != std::string::npos) {
            if(entry.find(comaDelimiter) < entry.find(colonDelimiter)) {
            std::string entryName = entry.substr(0, entry.find(comaDelimiter));
            std::string newValue = entry.substr(entry.find(comaDelimiter) + 1, entry.find(colonDelimiter) - entry.find(comaDelimiter) - 1);
            std::string newKey = entry.substr(entry.find(colonDelimiter) + 1, entry.size());



            if(newValue.empty() || newKey.empty()) {
              std::cerr<< "Error: invalid entry argument(s).\n";
              std::exit(1);
            }


            wObj.getCategory(category).getItem(item).deleteEntry(entryName);
            wObj.getCategory(category).getItem(item).addEntry(newKey, newValue);

            wObj.save(db);
            } else {
            std::string entryName = entry.substr(0, entry.find(colonDelimiter));
            std::string newKey = entry.substr(entry.find(colonDelimiter) + 1, entry.find(comaDelimiter) - entry.find(colonDelimiter) - 1);
            std::string newValue = entry.substr(entry.find(comaDelimiter) + 1, entry.size());

            if(newValue.empty() || newKey.empty()) {
              std::cerr<< "Error: invalid entry argument(s).\n";
              std::exit(1);
            }


            wObj.getCategory(category).getItem(item).deleteEntry(entryName);
            wObj.getCategory(category).getItem(item).addEntry(newKey, newValue);

            wObj.save(db);
            }

          } else if(entry.find(colonDelimiter) != std::string::npos) {

            std::string entryName = entry.substr(0, entry.find(colonDelimiter));
            std::string newKey = entry.substr(entry.find(colonDelimiter) + 1, entry.size());
            std::string keyValue = wObj.getCategory(category).getItem(item).getEntry(entryName);

            if(newKey.empty()) {
              std::cerr<< "Error: invalid entry argument(s).\n";
              std::exit(1);
            }

            wObj.getCategory(category).getItem(item).deleteEntry(entryName);
            wObj.getCategory(category).getItem(item).addEntry(newKey, keyValue);
            
            wObj.save(db);


          } else if(entry.find(comaDelimiter) != std::string::npos) {

            std::string entryName = entry.substr(0, entry.find(comaDelimiter));
            std::string newValue = entry.substr(entry.find(comaDelimiter) + 1, entry.size());

            if(newValue.empty()) {
              std::cerr<< "Error: invalid entry argument(s).\n";
              std::exit(1);
            }


            wObj.getCategory(category).getItem(item).addEntry(entryName, newValue);
            
            wObj.save(db);

          } else {
            std::cerr<< "Error: Invalid delimiter\n";
            std::exit(1);
          }

      }
      break;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    };
  }
  case Action::DELETE: {
    try{
      std::string category = args.count("category") ? args["category"].as<std::string>() : "";
      std::string item = args.count("item") ? args["item"].as<std::string>() : "";
      std::string entry = args.count("entry") ? args["entry"].as<std::string>() : "";

      if(category.empty() && item.empty() && entry.empty()) {
        std::cerr<< "Error: missing category, item or entry argument(s)\n";
      } else if(!category.empty() && item.empty() && entry.empty()) {
        wObj.deleteCategory(category);
        wObj.save(db);
      } else if(!category.empty() && !item.empty() && entry.empty()) {
        wObj.getCategory(category).deleteItem(item);
        wObj.save(db);
      } else {
        wObj.getCategory(category).getItem(item).deleteEntry(entry);
        wObj.save(db);
      }

      break;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::exit(1);
    };
  }
  default:
    throw std::runtime_error("Unknown action not implemented");
  }
  } catch(std::exception &e) {
    std::cerr << "Error:invalid action argument(s)." << std::endl;
    std::exit(1);
  };

  return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371pass", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371pass database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action", "Action to take, can be: 'create', 'read', 'update', 'delete'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action to a category (e.g., if you want to add a category, set the"
      " action argument to 'add' and the category argument to your chosen"
      " category identifier).",
      cxxopts::value<std::string>())(

      "item",
      "Apply action to an item (e.g., if you want to add an item, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier and the item argument to the item identifier).",
      cxxopts::value<std::string>())(

      "entry",
      "Apply action to an entry (e.g., if you want to add an entry, set the "
      "action argument to 'add', the category argument to your chosen category "
      "identifier, the item argument to your chosen item identifier, and the "
      "entry argument to the string 'key,value'). If there is no comma, an "
      "empty entry is inserted. If you are simply retrieving an entry, set the "
      "entry argument to the 'key'. If you are updating an entry key, use a : "
      "e.g., oldkey:newkey,newvalue.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}


bool compareChar(const char & c1, const char & c2)
{
    if (c1 == c2)
        return true;
    else if (std::toupper(c1) == std::toupper(c2))
        return true;
    return false;
}

bool caseInSensStringCompare(const std::string & str1, const std::string &str2)
{
    return ( (str1.size() == str2.size() ) &&
             std::equal(str1.begin(), str1.end(), str2.begin(), &compareChar) );
}
// TODO Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
  std::string input = args["action"].as<std::string>();

  if(caseInSensStringCompare(input, "create")) {
    return Action::CREATE;
  } else if(caseInSensStringCompare(input, "read")) {
    return Action::READ;
  } else if(caseInSensStringCompare(input, "update")) {
    return Action::UPDATE;
  } else if(caseInSensStringCompare(input, "delete")) {
    return Action::DELETE;
  } else {
    throw std::invalid_argument("action");
  }
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::cout << getJSON(wObj);
std::string App::getJSON(Wallet &wObj) { 
  // return "{}";
  // Only uncomment this once you have implemented the functions used!
  return wObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(wObj, c);
std::string App::getJSON(Wallet &wObj, const std::string &c) {
  // return "{}";
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  return cObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Item in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::cout << getJSON(wObj, c, i);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i) {
  // return "{}";
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  const auto iObj = cObj.getItem(i);
  return iObj.str();
}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Entry in a Wallet object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  Wallet wObj{};
//  std::string c = "category argument value";
//  std::string i = "item argument value";
//  std::string e = "entry argument value";
//  std::cout << getJSON(wObj, c, i, e);
std::string App::getJSON(Wallet &wObj, const std::string &c,
                         const std::string &i, const std::string &e) {
  // return "{}";
  // Only uncomment this once you have implemented the functions used!
  auto cObj = wObj.getCategory(c);
  auto iObj = cObj.getItem(i);
  return iObj.getEntry(e);
}