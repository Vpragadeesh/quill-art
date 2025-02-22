#include "path.hpp"

Path::Path(const std::string& d)
    : d_(d)
{
}

std::string Path::toSVG() const {
    // Example: <path d="M10 10 H 80 V 80 H 10 Z" stroke="black" fill="transparent"/>
    return "<path d=\"" + d_ + "\" stroke=\"black\" fill=\"transparent\" />";
}
