#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../shapes/shape.hpp"

class G : public virtual Shape {
public:
    void addShape(std::unique_ptr<Shape> shape);

    virtual std::string toSVG() const override;

private:
    std::vector<std::unique_ptr<Shape>> shapes_;
};
