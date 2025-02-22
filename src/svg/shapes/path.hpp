#pragma once
#include"shape.hpp"
#include<string>
#include<sstream>

// A simple Path class that holds an SVG path string (e.g., "M10 10 H 80 V 80 H 10 Z").
class Path : public Shape {
public:
    explicit Path(const std::string& d, std::string& stroke, std::string& fill)
        : d_(d), stroke_(stroke), fill_(fill) {} // 'd' is the "d" attribute in <path d="..."/>
    
    std::string toSVG() const override  {
        // Example: <path d="M10 10 H 80 V 80 H 10 Z" stroke="black" fill="transparent"/>
        std::stringstream ss;
        ss << "<path d=\"" << d_ << "\" stroke=\"" << stroke_ << "\" fill=\"" << fill_ << "\"/>";
        return ss.str();
    }

private:
    std::string d_;
    std::string stroke_;
    std::string fill_;
};
