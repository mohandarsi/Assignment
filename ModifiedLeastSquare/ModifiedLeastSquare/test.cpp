
#include<fstream>
#include<iostream>
#include<sstream>
#include<cmath>

#include "Interfaces.h"

/*
X = r * cosine(angle)
Y = r * sine(angle)

X = Cx + (r * cosine(angle))
Y = Cy + (r * sine(angle))

*/

#define ASSERT_EQ(VALUE, EXPECTED) \
      if(1){ \
        auto testValue = (VALUE); auto expectedValue = (EXPECTED); \
        if (testValue != expectedValue)  \
        { \
            std::ostringstream assertStr; \
            assertStr << "\"" << #VALUE << " (" << testValue << ")  == " << #EXPECTED << " (" << expectedValue << ")\" "; \
            throw std::exception(assertStr.str().c_str()); \
        } \
      }


void testRadiusOne()
{
    std::vector<Point2D> vecPoints = { { -1,0 },{ 0,1 },{ 1,0 },{ 0,-1 } };
    auto circle = SSM(vecPoints);
    ASSERT_EQ(circle.centre.x, 0.0);
    ASSERT_EQ(circle.centre.y, 0.0);
    ASSERT_EQ(circle.radius, 1.0);
}

void testCollinearCircle()
{
    auto exce = false;
    try {

        std::vector<Point2D> vecPoints = { { -5,5 },{ 5,5 },{ 0,5 } };
        auto circle = SSM(vecPoints);
    }
    catch (...)
    {
        exce = true;
    }
    ASSERT_EQ(exce, true);
}

void testRadiusFive()
{
    std::vector<Point2D> vecPoints;

    const double pi = std::acos(-1);
    double angle[] = { 0,pi/4,pi/2,pi };
    for (int i = 0; i < 4; i++)
    {
        auto X = 5 + (5 * std::cos(angle[i]));
        auto  Y = 5 + (5 * std::sin(angle[i]));
        vecPoints.push_back({ X,Y });
    }
    auto circle = SSM(vecPoints);
    ASSERT_EQ(std::ceil(circle.radius), 5.0);
}

void RunTests()
{
    testRadiusOne();
    testCollinearCircle();
    testRadiusFive();
}
