#include "rectangle.hpp"
#include <stdexcept>
#include <ostream>
#include "base-types.hpp"

namespace yakubov
{
    Rectangle::Rectangle(const point_t& position, const double width, const double height) :
        position_(position),
        width_(width),
        height_(height)
    {
        if (width_ <= 0.0)
        {
            throw std::invalid_argument("Error: Width cannot be <= 0.0");
        }
        if (height_ <= 0.0)
        {
            throw std::invalid_argument("Error: Height cannot be <= 0.0");
        }
    }

    double Rectangle::getArea() const noexcept
    {
        return width_ * height_;
    }

    rectangle_t Rectangle::getFrameRect() const
    {
        return { position_, width_, height_ };
    }

    void Rectangle::print(std::ostream& out) const
    {
        const double area = getArea();
        out << "Rectangle.\n";
        out << "Position: x = " << position_.x << ", y = " << position_.y << '\n';
        out << "height = " << height_ << " width = " << width_ << '\n';
        out << "Area = " << area << '\n';
    }

    void Rectangle::scale(const double factor)
    {
        if (factor <= 0.0)
        {
            throw std::invalid_argument("Error: Scale factor cannot be <= 0.0");
        }

        height_ *= factor;
        width_ *= factor;
    }

    void Rectangle::move(const point_t& newPosition) noexcept
    {
        position_ = newPosition;
    }

    void Rectangle::move(const double dx, const double dy) noexcept
    {
        position_.x += dx;
        position_.y += dy;
    }

    point_t Rectangle::getPos() const noexcept
    {
        return position_;
    }
}
