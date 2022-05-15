// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// A category contains one or more Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H
#include <iostream>
#include <vector>
#include <algorithm>
#include "item.h"


class Category {
    private:
        std::string ident;
        std::vector<Item> items;

    public:
        Category(std::string ident);
        ~Category();

        const unsigned int size() const;
        const bool empty() const;

        const std::string &getIdent() const;
        const std::vector<Item> &getItems() const;
        void setIdent(const std::string &newIdent);
        Item &newItem(const std::string &itemIdent);
        bool addItem(const Item &itemToAdd);
        Item &getItem(const std::string &itemToRetrieve);
        bool deleteItem(const std::string &itemToDelete);
        friend bool operator==(const Category& lhs, const Category& rhs);
        const std::string str() const;
};

#endif // CATEGORY_H
