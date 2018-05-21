#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

struct Point
{
    double x, y;

    Point() = default;

    Point(double x, double y) : x(x), y(y) {}

    static void swap(Point &point1, Point &point2)
    {
        double temp;

        temp = point1.x;
        point1.x = point2.x;
        point2.x = temp;

        temp = point1.y;
        point1.y = point2.y;
        point2.y = temp;
    }

    void print()
    {
        std::cout<<"( "<<x<<", "<<y<<" )";
    }
};

#endif //POINT_HPP
