#pragma once
#include <string>

// The base Shape class is abstract because of the pure virtual method toSVG().
class Shape {
public:
  virtual ~Shape() = default;

  // Convert this shape to an SVG element string.
  virtual std::string toSVG() const = 0;
};
