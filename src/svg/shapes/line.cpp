#include "line.hpp"
#include <string>

Line::Line(double x1, double y1, double x2, double y2)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

std::string Line::toSVG() const {
    // Example: <line x1="0" y1="0" x2="100" y2="100" stroke="black" />
    return "<line x1=\"" + std::to_string(x1_) +
           "\" y1=\"" + std::to_string(y1_) +
           "\" x2=\"" + std::to_string(x2_) +
           "\" y2=\"" + std::to_string(y2_) +
           "\" stroke=\"black\" />";
}
