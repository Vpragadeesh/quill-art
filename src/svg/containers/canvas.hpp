#pragma once
#include <vector>
#include <memory>
#include <memory>
#include "../shapes/shape.hpp"


class Canvas {
public:
    // Add a shape to the canvas
    void addShape(std::unique_ptr<Shape> shape);

    // Clear all shapes
    void clear();

    // Generate an SVG string containing all shapes
    std::string toSVG(int width = 500, int height = 500) const;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};
