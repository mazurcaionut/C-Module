// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2021/22)
// Department of Computer Science, Swansea University
//
// Author: 984174
//
// Canvas: https://canvas.swansea.ac.uk/courses/24793
// -----------------------------------------------------
// The root object that holds all data for 371pass. This
// class contains Categories, which in turn hold Items,
// which hold a mapping of entries.
// -----------------------------------------------------

#ifndef WALLET_H
#define WALLET_H
#include <iostream>
#include <vector>
#include "category.h"
#include <fstream>


class Wallet {
    private:
        std::vector<Category> categories;

    public:
        Wallet();
        ~Wallet();

        const unsigned int size() const;
        const bool empty() const;

        Category &newCategory(const std::string &categoryIdent);
        bool addCategory(const Category &categoryToAdd);
        Category &getCategory(const std::string &categoryToRetrieve);
        bool deleteCategory(const std::string &categoryToDelete);
        void load(const std::string &databaseName);
        void save(const std::string &databaseName);
        friend bool operator==(const Wallet& lhs, const Wallet& rhs);
        const std::string str() const;
};

#endif // WALLET_H
