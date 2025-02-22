#include "circle.hpp"
#include <string>

// Constructor definition
Circle::Circle(double cx, double cy, double r)
    : cx_(cx), cy_(cy), r_(r) {}

// Return an SVG representation of a circle.
std::string Circle::toSVG() const {
    // Example: <circle cx="100" cy="100" r="50" stroke="black" fill="transparent" />
    return "<circle cx=\"" + std::to_string(cx_) +
           "\" cy=\"" + std::to_string(cy_) +
           "\" r=\"" + std::to_string(r_) +
           "\" stroke=\"black\" fill=\"transparent\" />";
}
