#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

void printStatus(const double& area, const yakubov::rectangle_t& rect)
{
    std::cout << "Area = " << area << '\n';
    std::cout << "Frame Rects" << '\n';
    std::cout << "center (" << rect.pos.x << ", " << rect.pos.y
        << ") width = " << rect.width << " height = " << rect.height << '\n';
}

int main()
{
    yakubov::point_t point = { 32, 25 };
    yakubov::Rectangle rect(point, 30, 40);
    yakubov::Circle circle({ 100, 150 }, 50);
    yakubov::Shape* array[2] = { &rect, &circle };

    point = { 25, 25 };

    for (int i = 0; i < 2; i++)
    {
        std::cout << "    --------   *   ---------" << '\n';

        array[i]->print(std::cout);
        printStatus(array[i]->getArea(), array[i]->getFrameRect());

        std::cout << "    -----------------" << '\n';

        std::cout << "Move to (25, 25)" << '\n';
        array[i]->move(point);
        array[i]->print(std::cout);
        printStatus(array[i]->getArea(), array[i]->getFrameRect());

        std::cout << "    -----------------" << '\n';

        std::cout << "Move +5, -7" << '\n';
        array[i]->move(5, -7);
        array[i]->print(std::cout);
        printStatus(array[i]->getArea(), array[i]->getFrameRect());

        std::cout << "    -----------------" << '\n';

        std::cout << "Scale 2.3" << '\n';
        array[i]->scale(2.3);
        array[i]->print(std::cout);
        printStatus(array[i]->getArea(), array[i]->getFrameRect());

        std::cout << "    --------   *   ---------" << '\n';
    }

    return 0;
}