#pragma once

class Shape {
    public:

    Shape();
    virtual ~Shape();
    virtual std::string to_string() const = 0;
    virtual void centre_at(double x, double y) = 0;
};

    struct Circle : public Shape {
    
    private:
        double x;
        double y;
        double r;
    
    public:
        Circle(double x, double y, double r);
        virtual ~Circle();
        virtual std::string to_string() const;
        virtual void centre_at(double x, double y);


};