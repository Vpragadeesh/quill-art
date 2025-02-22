#include "rect.hpp"
#include <string>

Rect::Rect(double x, double y, double width, double height)
    : x_(x), y_(y), width_(width), height_(height) {}

std::string Rect::toSVG() const {
    // Example: <rect x="10" y="10" width="100" height="50" stroke="black" fill="transparent" />
    return "<rect x=\"" + std::to_string(x_) +
           "\" y=\"" + std::to_string(y_) +
           "\" width=\"" + std::to_string(width_) +
           "\" height=\"" + std::to_string(height_) +
           "\" stroke=\"black\" fill=\"transparent\" />";
}
