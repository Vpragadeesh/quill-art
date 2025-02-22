#include "g.hpp"
#include <sstream>

void G::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

std::string G::toSVG() const {
    // Build a <g> tag with nested shapes
    std::ostringstream oss;
    oss << "<g>";

    for (const auto &shape : shapes_) {
        oss << "\n  " << shape->toSVG();
    }

    oss << "\n</g>";
    return oss.str();
}
