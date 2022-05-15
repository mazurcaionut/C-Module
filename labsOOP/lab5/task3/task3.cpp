#include <iostream>
#include "shape.h"
int main(int argc , char *argv[]) {
    Shape **xs = new Shape*[10];

    xs[0] = new Circle(0, 0, 1);
    xs[1] = new Rectangle(0, 1, 1, 0);
    xs[2] = new Triangle(0, 0, 1, 1, 0, 1);

    xs[3] = new Circle(2, 1, 1);
    xs[4] = new Rectangle(1, 4, 3, 1);
    xs[5] = new Triangle(1, 1, 2, 2, 1, 2);

    xs[6] = new Circle(3, 4, 2);
    xs[7] = new Rectangle(2, 5, 4, 2);
    xs[8] = new Triangle(2, 2, 3, 3, 2, 3);

    xs[9] = new Circle(4, 5, 2);

    for(int i = 0; i < 10; i++){
        std::cout << xs[i]->to_string() << std::endl;
        xs[i]->centre_at(2, 2);
        std::cout << xs[i]->to_string() << std::endl;
    }

    for (int i = 0; i < 10; i++){
        delete xs[i];
    }

    delete xs;
    return 0;
}