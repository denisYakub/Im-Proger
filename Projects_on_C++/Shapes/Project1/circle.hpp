#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iosfwd>
#include "shape.hpp"
#include "base-types.hpp"

namespace yakubov
{
    class Circle : public Shape
    {
    public:
        Circle(const point_t& position, const double radius);

        double getArea() const noexcept override;

        rectangle_t getFrameRect() const override;

        void print(std::ostream& out) const override;

        void scale(const double factor) override;

        void move(const point_t& newPosition) noexcept override;

        void move(const double dx, const double dy) noexcept override;

        point_t getPos() const noexcept override;
    private:
        point_t center_;
        double radius_;
    };
}

#endif