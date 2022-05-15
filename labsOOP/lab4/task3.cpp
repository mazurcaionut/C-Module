#include <iostream>
#include "cat.h"

int main(int argc, char const *argv[])
{
    int params = argc - 1;
    int catNum = (params % 2 == 0) ? params / 2 : (params / 2) + 1;

    std::cout << "Allocating clowder of size " << catNum;

    Cat *cats = new Cat[catNum]();

    int j = 1;
    for (int i = 0; i < catNum; i++)
    {
        if (params % 2 == 1 && i + 1 == catNum)
        {
            cats[i] = std::move(Cat(argv[j]));
        }
        else
        {
            cats[i] = std::move(Cat(argv[j], std::stoi(argv[j + 1])));
        }
        j += 2;
    }

    for (int i = 0; i < catNum; i++)
    {
        std::cout << cats[i].get_name() << " has "
                  << cats[i].get_lives() << " lives." << std::endl;
    }

    delete[] cats;

    return 0;
}
