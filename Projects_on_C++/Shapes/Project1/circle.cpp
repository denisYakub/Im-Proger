#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <stdexcept>
#include <cmath>
#include <ostream>
#include "base-types.hpp"

namespace yakubov
{
    Circle::Circle(const point_t& center, const double radius) :
        center_(center),
        radius_(radius)
    {
        if (radius_ <= 0.0)
        {
            throw std::invalid_argument("Error: radius cannot be <= 0.0");
        }
    }

    double Circle::getArea() const noexcept
    {
        return radius_ * radius_ * M_PI;
    }

    rectangle_t Circle::getFrameRect() const
    {
        return { center_, 2 * radius_, 2 * radius_ };
    }

    void Circle::print(std::ostream& out) const
    {
        const double area = getArea();
        out << "Circle.\n";
        out << "Position: x = " << center_.x << ", y = " << center_.y << '\n';
        out << "Radius = " << radius_ << '\n';
        out << "Area = " << area << '\n';
    }

    void Circle::scale(const double factor)
    {
        if (factor <= 0.0)
        {
            throw std::invalid_argument("Error: Scale factor cannot be <= 0.0");
        }

        radius_ *= factor;
    }

    void Circle::move(const point_t& newPosition) noexcept
    {
        center_ = newPosition;
    }

    void Circle::move(const double dx, const double dy) noexcept
    {
        center_.x += dx;
        center_.y += dy;
    }

    point_t Circle::getPos() const noexcept
    {
        return center_;
    }
}