#pragma once
#include <vector>
#include <memory>
#include <string>
#include "shapes/shape.hpp"
#include <sstream>


class Canvas {
public:
    // Add a shape to the canvas
    void addShape(std::unique_ptr<Shape> shape) {
        shapes_.push_back(std::move(shape));
    }

    // Clear all shapes
    void clear() {
        shapes_.clear();
    }

    // Generate an SVG string containing all shapes
    std::string toSVG(int width = 500, int height = 500) const {
        // We'll use an std::ostringstream to build the SVG string
        std::ostringstream oss;
        
        // SVG Header
        oss << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << width << "\" height=\"" << height << "\">\n";
        // Add each shape
        for (const auto &shape : shapes_) {
            oss << "  " << shape->toSVG() << "\n";
        }
    
        // Close the SVG tag
        oss << "</svg>\n";
    
        return oss.str();
    }
    

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};
