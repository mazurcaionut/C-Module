#pragma once

class Cat
{

private:
    std::string name;
    unsigned int lives;

public:
    Cat();
    Cat(std::string name);
    Cat(std::string name, unsigned int lives);
    Cat(Cat &&other);
    ~Cat();

    Cat &operator=(Cat &&other);
    // {
    //     name = std::move(other.get_name());
    //     lives = std::move(other.get_lives());

    //     other.set_lives(0);
    //     other.set_name("");

    //     return *this;
    // }

    const std::string &get_name();
    const unsigned int &get_lives();

    void set_name(const std::string &name);
    void set_lives(const unsigned int &lives);
};
