#include "canvas.hpp"
#include <sstream>
#include <string>


// Add a shape to the canvas
void Canvas::addShape(std::unique_ptr<Shape> shape) {
    shapes_.push_back(std::move(shape));
}

// Clear all shapes from the canvas
void Canvas::clear() {
    shapes_.clear();
}

// Generate an SVG string containing all shapes
std::string Canvas::toSVG(int width, int height) const {
    // We'll use an std::ostringstream to build the SVG string
    std::ostringstream oss;
    
    // SVG Header
    oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\">\n";

    // Add each shape
    for (const auto &shape : shapes_) {
        oss << "  " << shape->toSVG() << "\n";
    }

    // Close the SVG tag
    oss << "</svg>\n";

    return oss.str();
}
