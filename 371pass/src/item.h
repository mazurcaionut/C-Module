// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// An Item class contains multiple 'entries' as
// key/value pairs (e.g., a key might be 'username'
// and a value would be the username, another might be
// 'url' and the value is the website address the
// username is for.
// -----------------------------------------------------
#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "lib_json.hpp"

using json = nlohmann::json;

class Item {
    private:
        std::string ident;
        std::unordered_map<std::string, std::string> entries;

    public:
        Item();
        Item(std::string ident);
        ~Item();

        const unsigned int size() const;
        const bool empty() const;

        const std::string &getIdent() const;
        const std::unordered_map<std::string, std::string> &getEntries() const;
        void setIdent(const std::string &newIdent);
        bool addEntry(const std::string &key, const std::string &value);
        const std::string &getEntry(const std::string &key);
        bool deleteEntry(const std::string &key);
        friend bool operator==(const Item& lhs, const Item& rhs);
        const std::string str() const;
};

#endif // ITEM_H
