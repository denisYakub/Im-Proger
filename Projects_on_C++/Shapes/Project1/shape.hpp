#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>
#include "base-types.hpp"

namespace yakubov
{
    class Shape
    {
    public:
        virtual ~Shape() = default;

        virtual void move(const point_t& newPosition) noexcept = 0;

        virtual void move(const double dx, const double dy) noexcept = 0;

        virtual double getArea() const noexcept = 0;

        virtual rectangle_t getFrameRect() const = 0;

        virtual void print(std::ostream& out) const = 0;

        virtual void scale(const double factor) = 0;

        virtual point_t getPos() const noexcept = 0;
    };
}

#endif
