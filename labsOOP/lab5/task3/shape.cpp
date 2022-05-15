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

Triangle::Triangle(double x0, double y0, double x1, double y1, double x2, double y2) : x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {
    // std::cout<<"Rectangle constuctor called with x0, y0, x1, y1, x2, y2 ...\n";
}

Triangle::~Triangle(){
    // std::cout << "Triangle deconstructor called ...\n";
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

double mySqrt(double num){

    double lower_bound=0; 
    double upper_bound=num;
    double temp=0;                    

    int nCount = 50;

    while(nCount != 0)
    {
            temp=(lower_bound+upper_bound)/2;
            if(temp*temp==num) 
            {
                    return temp;
            }
            else if(temp*temp > num)

            {
                    upper_bound = temp;
            }
            else
            {
                    lower_bound = temp;
            }
    nCount--;
    }
    return temp;
}

int pow (int x, int power){

    for(int i = 1; i < power; i++){
        x = x*x;
    }

    return x;
}
float distance(int x1, int y1, int x2, int y2)
{
    int pow1 = pow(x2 - x1, 2);
    int pow2 = pow(y2 - y1, 2);

    return mySqrt(pow1 + pow2);
}

std::string Triangle::to_string() const {
    std::stringstream sstr;
    sstr << "Triangle at [(" << x0 << ", " << y0 << "), (" << x1 <<", " << y1 <<"), (" << x2 <<", " << y2 <<")] with side lengths " 
    << distance(x0, y0, x1, y1) << ", " <<distance(x0, y0, x2, y2) << ", and " <<distance(x1, y1, x2, y2)<<"..."<<std::endl;
    std::string str = sstr.str();
    return str;
}

void Triangle::centre_at(double x, double y){

    double xc = (x0 + x1 + x2) / 3;
    double yc = (y0 + y1 + y2) / 3;

    double xval = xc - x;
    double yval = yc - y;


    this->x0 = x0 - xval;
    this->y0 = y0 - yval;

    this->x1 = x1 - xval;
    this->y1 = y1 - yval;

    this->x2 = x2 - xval;
    this->y2 = y2 - yval;
   
}
