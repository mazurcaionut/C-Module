#include <iostream>
#include <sstream>
#include "shape.h"


Shape::Shape (){
    std::cout <<"Shape constructor called...\n";
}

Shape::~Shape (){
    std::cout << "Shape deconstructor called...\n";
}

Circle::Circle(double x, double y, double r) : x(x), y(y), r(r){
    std::cout << "Circle constructor called with x, y and r ...\n";
}

Circle::~Circle(){
    std::cout << "Circle deconstructor called ...\n";
}

std::string Circle::to_string() const {
    std::stringstream sstr;
    sstr << "Circle centered at (" << x << ", " << y << ") with radius " << r << std::endl;
    std::string str = sstr.str();
    return str;
}

void Circle::centre_at(double x, double y){

    this->x = x;
    this->y = y;
}

