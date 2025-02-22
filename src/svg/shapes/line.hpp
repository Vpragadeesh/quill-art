#pragma once
#include "shape.hpp"
#include <string>

class Line : public Shape {
public:
    Line(double x1, double y1, double x2, double y2);

    std::string toSVG() const override;

private:
    double x1_;
    double y1_;
    double x2_;
    double y2_;
};
