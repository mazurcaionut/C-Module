// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(std::string ident) : ident(ident){}


Category::~Category(){}


// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
const unsigned int Category::size() const
{
    return this->items.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of Items in the Category is zero, false otherwise.
//
// Example:
//  Category c{"categoryIdent"};
//  auto empty = c.empty();

const bool Category::empty() const
{
    return this->items.empty();
}

// TODO Write a function, getIdent, that returns the identifier for the
//  Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
const std::string &Category::getIdent() const
{
    return this->ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string &newIdent)
{
    this->ident = newIdent;
}


// Function that retrieves all entries
const std::vector<Item> &Category::getItems() const
{
    return this->items;
}

// TODO Write a function, newItem, that takes one parameter, an Item identifier,
//  (a string) and returns the Item object as a reference. If an object with the
//  same identifier already exists, then the existing object should be returned.
//  Throw a std::runtime_error if the Item object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
Item &Category::newItem(const std::string &itemIdent)
{

    const auto &it = std::find_if(this->items.begin(),
                                 this->items.end(), 
                                 [&itemIdent](Item &current)
                                    { 
                                        return current.getIdent() == itemIdent;
                                    });


    if(it != this->items.end()) {
        return *it;
    } else {

        if(itemIdent.empty()) {
            throw std::runtime_error("String is emtpy");
        }


        Item itemToAdd{itemIdent};

        this->items.push_back(itemToAdd);

        const auto &itNew = std::find_if(this->items.begin(),
                                this->items.end(), 
                                [&itemIdent](Item &current)
                                { 
                                    return current.getIdent() == itemIdent;
                                });


        return *itNew;
    }
}

// TODO Write a function, addItem, that takes one parameter, an Item object,
//  and returns true if the object was successfully inserted. If an object with
//  the same identifier already exists, then the contents should be merged and
//  return false.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
bool Category::addItem(const Item &itemToAdd)
{
    const auto &it = std::find_if(this->items.begin(),
                                 this->items.end(), 
                                 [&itemToAdd](Item &current)
                                    { 
                                        return current.getIdent() == itemToAdd.getIdent();
                                    });

    if(it != this->items.end()) {

        for(const auto &currentValue: itemToAdd.getEntries()) {
            (*it).addEntry(currentValue.first, currentValue.second);
        }

        // (*it).getEntries().insert(itemToAdd.getEntries().begin(), itemToAdd.getEntries().end());
        // for(const auto& currentValue: (*it).getEntries()) {

        // }

        return false;
    } else {

        this->items.push_back(itemToAdd);

        return true;
    }
}

// TODO Write a function, getItem, that takes one parameter, an Item
//  identifier (a string) and returns the Item as a reference. If no Item
//  exists, throw an appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  auto iObj = cObj.getItem("itemIdent");
Item &Category::getItem(const std::string &itemToRetrieve)
{
    const auto &it = std::find_if(this->items.begin(),
                                 this->items.end(), 
                                 [&itemToRetrieve](Item &current)
                                    { 
                                        return current.getIdent() == itemToRetrieve;
                                    });

    if(it != this->items.end()) {
        return *it;
    } else {
        if(itemToRetrieve.length() != 0) {
            throw std::out_of_range("Error:invalid item argument(s).");
        } else {
            throw std::invalid_argument("Error:missing item argument(s).");
        }
    }
}

// TODO Write a function, deleteItem, that takes one parameter, an Item
//  identifier (a string), deletes it from the container, and returns true if
//  the Item was deleted. If no Item exists, throw an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("itemIdent");
//  bool result = cObj.deleteItem("itemIdent");
bool Category::deleteItem(const std::string &itemToDelete)
{
    const auto &it = std::find_if(this->items.begin(),
                                 this->items.end(), 
                                 [&itemToDelete](Item &current)
                                    { 
                                        return current.getIdent() == itemToDelete;
                                    });

    if(it != this->items.end()) {

        this->items.erase(it);

        return true;
    } else {
        throw std::out_of_range("action");
    }
}

// TODO Write an == operator overload for the Category class, such that two
//  Category objects are equal only if they have the same identifier and same
//  Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj1.newItem("itemIdent");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
bool operator==(const Category& lhs, const Category& rhs)
{
    //make sure to compare the contained items in each category
    return lhs.ident.compare(rhs.ident) == 0 && lhs.str() == rhs.str();
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
const std::string Category::str() const
{
    json j;

    for(auto &currentValue: this->items) {
        j[currentValue.getIdent()] = json::parse(currentValue.str());
    }

    return j.dump();
}