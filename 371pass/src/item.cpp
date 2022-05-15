// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------


#include "item.h"


// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Item iObj{"identIdent"};

Item::Item(){}

Item::Item(std::string ident) : ident(ident){}


Item::~Item(){}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of entries in the Item contains.
//
// Example:
//  Item iObj{"identIdent"};
//  auto size = iObj.size();

const unsigned int Item::size() const
{
    // return 0;
    
    // unsigned int count = 0;
    // for (auto it = this->entries.begin(); it != this->entries.end(); it++) {
    //     count+=1;
    // }
    return this->entries.size();
}

// TODO Write a function, empty, that takes no parameters and returns true
//  if the number of entries in the Item is zero, false otherwise.
//
// Example:
//  Item iObj{"identIdent"};
//  auto empty = iObj.empty();

const bool Item::empty() const
{
    return this->entries.empty();
}
// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Item identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.setIdent("identIdent2");
void Item::setIdent(const std::string &newIdent)
{
    this->ident = newIdent;
}

// TODO Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"identIdent"};
//  auto ident = iObj.getIdent();

const std::string &Item::getIdent() const
{
    return this->ident;
}


// Function that retrieves all entries
const std::unordered_map<std::string, std::string> &Item::getEntries() const
{
    return this->entries;
}

// TODO Write a function, addEntry, that takes two parameters, an entry
//  key and value and returns true if the entry was inserted into the
//  container or false if the entry already existed and was replaced.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
bool Item::addEntry(const std::string &key, const std::string &value)
{
    auto alreadyExisted = this->entries.find(key);

    if(alreadyExisted != this->entries.end()) {
        this->entries[key] = value;

        return false;
    } else {
        this->entries.insert({key, value});

        return true;
    }
}

// TODO Write a function, getEntry, that takes one parameter, an entry
//  key and returns it's value. If no entry exists, throw an appropriate
//  exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  auto value = iObj.getEntry("key");

const std::string &Item::getEntry(const std::string &key)
{
    // return "";
    auto alreadyExisted = this->entries.find(key);

    if(alreadyExisted != this->entries.end()) {

        return this->entries[key];
    } else {
        if(key.length() != 0) {
            throw std::out_of_range("Error:invalid entry argument(s).");
        } else {
            throw std::invalid_argument("Error:missing entry argument(s).");
        }
    }
}

// TODO Write a function, deleteEntry, that takes one parameter, an entry
//  key, deletes it from the container, and returns true if the Item was
//  deleted. If no entry exists, throw an appropriate exception.
//
// Example:
//  Item iObj{"identIdent"};
//  iObj.addEntry("key", "value");
//  iObj.deleteEntry("key");

bool Item::deleteEntry(const std::string &key)
{
    auto alreadyExisted = this->entries.find(key);

    if(alreadyExisted != this->entries.end()) {

        this->entries.erase(key);

        return true;
    } else {
        throw std::out_of_range("action");
    }
}

// TODO Write an == operator overload for the Item class, such that two
//  Item objects are equal only if they have the same identifier and same
//  entries.
//
// Example:
//  Item iObj1{"identIdent"};
//  iObj1.addEntry("key", "value");
//  Item iObj2{"identIdent2"};
//  if(iObj1 == iObj2) {
//    ...
//  }
bool operator==(const Item& lhs, const Item& rhs)
{
    return lhs.ident.compare(rhs.ident) == 0 
        && std::equal(lhs.entries.begin(), lhs.entries.end(), rhs.entries.begin());
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
const std::string Item::str() const
{
    // json j(this->entries);
    json j;

    for(const auto &currentEntry: this->entries) {
        j[currentEntry.first] = currentEntry.second;
    }

    return j.dump();
}