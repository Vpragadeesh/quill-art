#pragma once
#include "shape.hpp"
#include <string>

class Circle : public Shape {
public:
    // Constructor
    Circle(double cx, double cy, double r);

    // Implementation of the pure virtual method from Shape
    std::string toSVG() const override;

private:
    double cx_;  // Center x
    double cy_;  // Center y
    double r_;   // Radius
};
