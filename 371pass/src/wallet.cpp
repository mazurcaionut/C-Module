// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------

#include "wallet.h"


using json = nlohmann::json;


// TODO Write a Wallet constructor that takes no parameters and constructs an
//  empty wallet.
//
// Example:
//  Wallet wObj{};
Wallet::Wallet(){}


Wallet::~Wallet(){}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories in the Wallet contains.
//
// Example:
//  Wallet wObj{};
//  auto size = wObj.size();

const unsigned int Wallet::size() const
{
    return this->categories.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of categories in the Wallet is zero, false otherwise.
//
// Example:
//  Wallet wwObj{};
//  auto isEmpty = wObj.empty();

const bool Wallet::empty() const
{
    return this->categories.empty();
}

// TODO Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
Category &Wallet::newCategory(const std::string &categoryIdent)
{
    const auto &it = std::find_if(this->categories.begin(),
                                 this->categories.end(), 
                                 [&categoryIdent](Category &current)
                                    { 
                                        return current.getIdent() == categoryIdent;
                                    });

    if(it != this->categories.end()) {
        return *it;
    } else {

        if(categoryIdent.empty()) {
            throw std::runtime_error("String is emtpy");
        }


        Category categoryToAdd{categoryIdent};

        this->categories.push_back(categoryToAdd);

        const auto &itNew = std::find_if(this->categories.begin(),
                                this->categories.end(), 
                                [&categoryIdent](Category &current)
                                { 
                                    return current.getIdent() == categoryIdent;
                                });

        return *itNew;
    }

}

// TODO Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged and then return false. Throw a std::runtime_error if the Category
//  object cannot be inserted into the container for whatever reason.
//
// Example:
//  Wallet wObj{};
//  Category cObj{"categoryIdent"};
//  wObj.addCategory(cObj);
bool Wallet::addCategory(const Category &categoryToAdd)
{
    const auto &it = std::find_if(this->categories.begin(),
                                 this->categories.end(), 
                                 [&categoryToAdd](Category &current)
                                    { 
                                        return current.getIdent() == categoryToAdd.getIdent();
                                    });

    if(it != this->categories.end()) {

        for(const auto &currentValue : categoryToAdd.getItems()) {
            (*it).addItem(currentValue);
        }

        return false;
    } else {

        this->categories.push_back(categoryToAdd);

        return true;
    }
}

// TODO Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category. If no Category exists, throw an
//  appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  auto cObj = wObj.getCategory("categoryIdent");
Category &Wallet::getCategory(const std::string &categoryToRetrieve)
{
    const auto &it = std::find_if(this->categories.begin(),
                                 this->categories.end(), 
                                 [&categoryToRetrieve](Category &current)
                                    { 
                                        return current.getIdent() == categoryToRetrieve;
                                    });

    if(it != this->categories.end()) {
        return *it;
    } else {
        if(categoryToRetrieve.length() != 0) {
            throw std::out_of_range("Error:invalid category argument(s).");
        } else {
            throw std::invalid_argument("Error:missing category argument(s).");
        }
    }
}

// TODO Write a function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes it from the container, and returns true if the
//  Category was deleted. If no Category exists, throw an appropriate exception.
//
// Example:
//  Wallet wObj{};
//  wObj.newCategory("categoryIdent");
//  wObj.deleteCategory("categoryIdent");
bool Wallet::deleteCategory(const std::string &categoryToDelete)
{
    const auto &it = std::find_if(this->categories.begin(),
                                 this->categories.end(), 
                                 [&categoryToDelete](Category &current)
                                    { 
                                        return current.getIdent() == categoryToDelete;
                                    });

    if(it != this->categories.end()) {

        this->categories.erase(it);

        return true;
    } else {
        throw std::out_of_range("action");
    }
}
// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this Wallet. If the file does open throw an
//  appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same key, the categories should be
//  merged (not replaced!). If you encounter two items with the same key in the
//  same category, the items should be merged (not replaced!). If you encounter
//  two entries with the same key in the same item, the entries should be merged
//  (undefined as to which value is picked). Two items in different categories
//  can have the same key, as can two entries in different items.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
//    {
//      "Category 1" : {
//        "Item 1":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value",
//          ...
//        },
//        "Item 2":  {
//          "detail 1 key": "detail 1 value",
//          "detail 2 key": "detail 2 value"
//        },
//        ...
//      },
//      "Category 2": {
//        "Item 1": {
//          "detail 1 key": "detail 1 value"
//        }
//        ...
//      }
//    }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
void Wallet::load(const std::string &fileName)
{
    std::ifstream dbFile(fileName);

    if(!dbFile.is_open()) {
        std::cerr<< "Could not open the file for reading!\n";
        std::exit(1);
    }

    json j;

    dbFile >> j;

    for(auto &categoryElem : j.items()) {
        
        auto &categoryAdded = newCategory(categoryElem.key());

        for(auto &categoryItem : categoryElem.value().items()) {

            auto &itemAdded = categoryAdded.newItem(categoryItem.key());

            for(auto &entryValue : categoryItem.value().items()) {

                itemAdded.addEntry(entryValue.key(), entryValue.value());

            }

        }
    }


}

// TODO Write a function ,save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the Wallet object
//  as JSON.
//
// Example:
//  Wallet wObj{};
//  wObj.load("database.json");
//  ...
//  wObj.save("database.json");
void Wallet::save(const std::string &fileName)
{
    json j;

    std::ofstream dbFile(fileName);

    if(!dbFile.is_open()) {
        // std::cerr<< "Could not open the file for reading!\n";
        std::exit(1);
    }

    j = json::parse(str());

    dbFile << j.dump();

    dbFile.close();
}

// TODO Write an == operator overload for the Wallet class, such that two
//  Wallet objects are equal only if they have the exact same data.
//
// Example:
//  Wallet wObj1{};
//  Wallet wObj2{};
//  if(wObj1 == wObj2) {
//    ...
//  }
bool operator==(const Wallet& lhs, const Wallet& rhs)
{
    // return lhs.ident.compare(rhs.ident) == 0;
    //make sure to compare the wallets
    return lhs.str() == rhs.str();
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Wallet.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  Wallet wObj{};
//  std::string s = wObj.str();
const std::string Wallet::str() const
{

    json j;

    for(const auto &currentValueCategory: this->categories) {
        j[currentValueCategory.getIdent()] = json::parse(currentValueCategory.str());
    }

    return j.dump();

}