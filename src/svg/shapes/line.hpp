#pragma once
#include "shape.hpp"
#include <sstream>
#include <string>

class Line : public Shape {
public:
  Line(double x1, double y1, double x2, double y2, std::string &stroke)
      : x1_(x1), y1_(y1), x2_(x2), y2_(y2), stroke_(stroke) {}
  std::string toSVG() const override {
    // Example: <line x1="0" y1="0" x2="100" y2="100" stroke="black" />
    std::stringstream ss;
    ss << "<line x1=\"" << x1_ << "\" y1=\"" << y1_ << "\" x2=\"" << x2_
       << "\" y2=\"" << y2_ << "\" stroke=\"" << stroke_ << "\"/>";
    return ss.str();
  }

private:
  double x1_;
  double y1_;
  double x2_;
  double y2_;
  std::string stroke_;
};
