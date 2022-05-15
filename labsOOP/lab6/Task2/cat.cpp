#include <iostream>
#include "cat.h"

Cat::Cat() : name("Tom"), lives(9)
{
    std::cout << "Default constructor called...\n";
}

Cat::Cat(std::string name) : name(name), lives(9)
{
    // std::cout << "Constructor called with name...\n";
}

Cat::Cat(std::string name, unsigned int lives) : name(name), lives(lives)
{
    // std::cout << "Constructor called with name and lives...\n";
}

Cat::Cat(Cat &&other)
{
    name = std::move(other.get_name());
    lives = std::move(other.get_lives());

    // other.set_lives(0);
    // other.set_name("");
}

Cat::~Cat()
{
    // std::cout << "Destructor called...\n";
}

Cat &Cat::operator=(Cat &&other)
{
    name = std::move(other.get_name());
    lives = std::move(other.get_lives());

    // other.set_lives(0);
    // other.set_name("");

    return *this;
}

const std::string &Cat::get_name()
{
    return this->name;
}

const unsigned int &Cat::get_lives()
{
    return this->lives;
}


bool operator==(const Cat& lhs, const Cat& rhs)
{
    return lhs.name.compare(rhs.name) == 0 && lhs.lives == rhs.lives;
}

std::ostream &operator<<(std::ostream &os, const Cat& cat)
{
    os << cat.name << " has " << cat.lives << " lives..."; 

    return os;
}

void Cat::set_name(const std::string &name)
{
    std::cout << "set_name called...\n";
    this->name = name;
}

void Cat::set_lives(const unsigned int &lives)
{
    std::cout << "set_lives called...\n";

    if (lives >= this->lives)
    {
        return;
    }

    if (lives == 0 && this->lives >= 0)
    {
        std::string newName = "The Cat formerly known as " + this->name;
        this->set_name(newName);
    }

    this->lives = lives;
}