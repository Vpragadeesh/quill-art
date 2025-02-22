#pragma once
#include "shape.hpp"
#include <string>

// A simple Path class that holds an SVG path string (e.g., "M10 10 H 80 V 80 H 10 Z").
class Path : public Shape {
public:
    explicit Path(const std::string& d);  // 'd' is the "d" attribute in <path d="..."/>
    
    std::string toSVG() const override;

private:
    std::string d_;
};
