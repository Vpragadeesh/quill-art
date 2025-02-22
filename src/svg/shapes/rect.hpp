#pragma once
#include"shape.hpp"
#include<string>
#include<sstream>

class Rect : public Shape {
public:
    Rect(double x, double y, double width, double height, std::string& stroke, std::string& fill)
        : x_(x), y_(y), width_(width), height_(height), stroke_(stroke), fill_(fill) {}

    std::string toSVG() const override {
        // Example: <rect x="10" y="10" width="100" height="50" stroke="black" fill="transparent" />
        // std::stringstream ss;
        std::stringstream ss;
        ss << "<rect x=\"" << x_ << "\" y=\"" << y_ << "\" width=\"" << width_ << "\" height=\"" << height_ << "\" stroke=\"" << stroke_ << "\" fill=\"" << fill_ << "\"/>";
        return ss.str();
    }

private:
    double x_;
    double y_;
    double width_;
    double height_;
    std::string stroke_;
    std::string fill_;
};
