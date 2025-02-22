#pragma once
#include"shape.hpp"
#include<string>
#include<sstream>

class Circle : public Shape {
public:
    // Constructor
    Circle(double cx, double cy, double r, std::string& stroke, std::string& fill)
        : cx_(cx), cy_(cy), r_(r), stroke_(stroke), fill_(fill) {}
    // Implementation of the pure virtual method from Shape
    std::string toSVG() const override {
        // Example: <circle cx="100" cy="100" r="50" stroke="black" fill="transparent" />
        std::stringstream ss;
        ss << "<circle cx=\"" << cx_ << "\" cy=\"" << cy_ << "\" r=\"" << r_ << "\" stroke=\"" << stroke_ << "\" fill=\"" << fill_ << "\"/>";
        return ss.str();
    }

private:
    double cx_;  // Center x
    double cy_;  // Center y
    double r_;   // Radius
    std::string stroke_;
    std::string fill_;
};
