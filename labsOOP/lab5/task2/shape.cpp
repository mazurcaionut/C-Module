#include <iostream>
#include <sstream>
#include "shape.h"


Shape::Shape (){
    // std::cout <<"Shape constructor called...\n";
}

Shape::~Shape (){
    // std::cout << "Shape deconstructor called...\n";
}

Circle::Circle(double x, double y, double r) : x(x), y(y), r(r){
    // std::cout << "Circle constructor called with x, y and r ...\n";
}

Circle::~Circle(){
    // std::cout << "Circle deconstructor called ...\n";
}

Rectangle::Rectangle(double x0, double y0, double x1, double y1) : x0(x0), y0(y0), x1(x1), y1(y1){
    // std::cout<<"Rectangle constuctor called with x0, y0, x1, y1 ...\n";
}

Rectangle::~Rectangle(){
    // std::cout << "Rectangle deconstructor called ...\n";
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

std::string Rectangle::to_string() const {
    std::stringstream sstr;
    sstr << "Rectangle at [(" << x0 << ", " << y0 << "), (" << x1 <<", " << y1 <<")] with width " << x1 - x0 << ", height " << y0 - y1 <<"..." <<std::endl;
    std::string str = sstr.str();
    return str;
}

void Rectangle::centre_at(double x, double y){

    double xc = (x1 - x0) / 2;
    double yc = (y0 - y1) / 2;

    
    double newx0 = x - xc;
    double newx1 = x + xc;
    double newy0 = y + yc;
    double newy1 = y - yc;

    this->x0 = newx0;
    this->y0 = newy0;
    this->x1 = newx1;
    this->y1 = newy1;
   
}
