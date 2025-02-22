#pragma once
#include "shape.hpp"
#include <string>

class Rect : public Shape {
public:
    Rect(double x, double y, double width, double height);

    std::string toSVG() const override;

private:
    double x_;
    double y_;
    double width_;
    double height_;
};
