#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iosfwd>
#include "shape.hpp"
#include "base-types.hpp"

namespace yakubov
{
    class Rectangle : public Shape
    {
    public:
        Rectangle(const point_t& position, const double width, const double height);

        double getArea() const noexcept override;

        rectangle_t getFrameRect() const override;

        void print(std::ostream& out) const override;

        void scale(const double factor) override;

        void move(const point_t& newPosition) noexcept override;

        void move(const double dx, const double dy) noexcept override;

        point_t getPos() const noexcept override;
    private:
        point_t position_;
        double width_;
        double height_;
    };
}

#endif
