#define BOOST_TEST_MODULE TEST_A2

#include <boost/test/included/unit_test.hpp>
#include <boost/test/tools/floating_point_comparison.hpp>

#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY_VALUE = 1e-10;

BOOST_AUTO_TEST_SUITE(circleTestSuite)

BOOST_AUTO_TEST_CASE(testFigureMovingToPoint)
{
    fernandez::Circle testCircle({ 0, 0 }, 5);
    const double initialWidth = testCircle.getFrameRect().width;
    const double initialHeight = testCircle.getFrameRect().height;
    const double initialArea = testCircle.getArea();

    testCircle.move({ 1.4, 2.1 });
    const double finalX = testCircle.getPos().x;
    const double finalY = testCircle.getPos().y;
    const double finalWidth = testCircle.getFrameRect().width;
    const double finalHeight = testCircle.getFrameRect().height;
    const double finalArea = testCircle.getArea();

    BOOST_CHECK_CLOSE(finalX, 1.4, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(finalY, 2.1, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialWidth, finalWidth, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialHeight, finalHeight, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialArea, finalArea, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testFigureMovingAlongAxes)
{
    fernandez::Circle testCircle({ -2, -4 }, 1);
    const double initialX = testCircle.getPos().x;
    const double initialY = testCircle.getPos().y;
    const double initialWidth = testCircle.getFrameRect().width;
    const double initialHeight = testCircle.getFrameRect().height;
    const double initialArea = testCircle.getArea();

    testCircle.move(6, 5);
    const double finalX = testCircle.getPos().x;
    const double finalY = testCircle.getPos().y;
    const double finalWidth = testCircle.getFrameRect().width;
    const double finalHeight = testCircle.getFrameRect().height;
    const double finalArea = testCircle.getArea();

    BOOST_CHECK_CLOSE(initialX + 6, finalX, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialY + 5, finalY, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialWidth, finalWidth, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialHeight, finalHeight, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialArea, finalArea, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testFigureAfterScaling)
{
    fernandez::Circle testCircle({ 1, 1 }, 5);
    const double initialX = testCircle.getPos().x;
    const double initialY = testCircle.getPos().y;
    const double initialArea = testCircle.getArea();

    testCircle.scale(2.25);
    const double finalX = testCircle.getPos().x;
    const double finalY = testCircle.getPos().y;
    const double finalArea = testCircle.getArea();

    BOOST_CHECK_CLOSE(initialX, finalX, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialY, finalY, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(finalArea, initialArea * 2.25 * 2.25, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testExceptionConstructor)
{
    BOOST_CHECK_THROW(fernandez::Circle({ 1, 2 }, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testNoExceptionConstructor)
{
    BOOST_CHECK_NO_THROW(fernandez::Circle({ 1, 2 }, 0.1));
}

BOOST_AUTO_TEST_CASE(testExceptionWhenScaling)
{
    fernandez::Circle testCircle({ 3, 1 }, 4);
    BOOST_CHECK_THROW(testCircle.scale(-1.1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testNoExceptionWhenScaling)
{
    fernandez::Circle testCircle({ 3, 1 }, 4);
    BOOST_CHECK_NO_THROW(testCircle.scale(0.1));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangleTestSuite)

BOOST_AUTO_TEST_CASE(testFigureMovingToPoint)
{
    fernandez::Rectangle testRectangle({ 1, 1 }, 3.2, 4.5);
    const double initialWidth = testRectangle.getFrameRect().width;
    const double initialHeight = testRectangle.getFrameRect().height;
    const double initialArea = testRectangle.getArea();

    testRectangle.move({ 2.1, 3.2 });
    const double finalX = testRectangle.getPos().x;
    const double finalY = testRectangle.getPos().y;
    const double finalWidth = testRectangle.getFrameRect().width;
    const double finalHeight = testRectangle.getFrameRect().height;
    const double finalArea = testRectangle.getArea();

    BOOST_CHECK_CLOSE(finalX, 2.1, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(finalY, 3.2, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialWidth, finalWidth, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialHeight, finalHeight, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialArea, finalArea, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testFigureMovingAlongAxes)
{
    fernandez::Rectangle testRectangle({ -1.2, 1.5 }, 2.4, 4.3);
    const double initialX = testRectangle.getPos().x;
    const double initialY = testRectangle.getPos().y;
    const double initialWidth = testRectangle.getFrameRect().width;
    const double initialHeight = testRectangle.getFrameRect().height;
    const double initialArea = testRectangle.getArea();

    testRectangle.move(1, -0.5);
    const double finalX = testRectangle.getPos().x;
    const double finalY = testRectangle.getPos().y;
    const double finalWidth = testRectangle.getFrameRect().width;
    const double finalHeight = testRectangle.getFrameRect().height;
    const double finalArea = testRectangle.getArea();

    BOOST_CHECK_CLOSE(initialX + 1, finalX, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialY - 0.5, finalY, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialWidth, finalWidth, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialHeight, finalHeight, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialArea, finalArea, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testFigureAfterScaling)
{
    fernandez::Rectangle testRectangle({ 1, 1 }, 3.2, 4.1);
    const double initialX = testRectangle.getPos().x;
    const double initialY = testRectangle.getPos().y;
    const double initialArea = testRectangle.getArea();

    testRectangle.scale(3.72);
    const double finalX = testRectangle.getPos().x;
    const double finalY = testRectangle.getPos().y;
    const double finalArea = testRectangle.getArea();

    BOOST_CHECK_CLOSE(initialX, finalX, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(initialY, finalY, ACCURACY_VALUE);
    BOOST_CHECK_CLOSE(finalArea, initialArea * 3.72 * 3.72, ACCURACY_VALUE);
}

BOOST_AUTO_TEST_CASE(testExceptionConstructorInvalidWidth)
{
    BOOST_CHECK_THROW(fernandez::Rectangle({ 1, 1 }, -1.8, 2), std::invalid_argument);
    BOOST_CHECK_THROW(fernandez::Rectangle({ 1, 1 }, 0, 2), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testExceptionConstructorInvalidHeight)
{
    BOOST_CHECK_THROW(fernandez::Rectangle({ 1, 1 }, 2, -1.5), std::invalid_argument);
    BOOST_CHECK_THROW(fernandez::Rectangle({ 1, 1 }, 2, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testNoExceptionConstructor)
{
    BOOST_CHECK_NO_THROW(fernandez::Rectangle({ 2, 1 }, 0.1, 1.2));
}

BOOST_AUTO_TEST_CASE(testExceptionWhenScaling)
{
    fernandez::Rectangle testRectangle({ 2, 1 }, 3.4, 5.8);
    BOOST_CHECK_THROW(testRectangle.scale(-1.1), std::invalid_argument);
    BOOST_CHECK_THROW(testRectangle.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testNoExceptionWhenScaling)
{
    fernandez::Rectangle testRectangle({ 2, 1 }, 3.4, 5.8);
    BOOST_CHECK_NO_THROW(testRectangle.scale(0.1));
}

BOOST_AUTO_TEST_SUITE_END()