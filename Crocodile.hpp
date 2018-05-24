#ifndef CROCODILE_HPP
#define CROCODILE_HPP

#include <utility>
#include "Point.hpp"

struct Crocodile
{
    Point point1{}, point2{};
    double length = 0, length_pow = 0;
    int connected_to_start = 0;
    double *connection_with_start = nullptr;
    bool connected_to_finish = false;

    Crocodile(double x1, double y1, double x2, double y2)
    {
        length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        length_pow = pow(length, 2);

        point1 = Point(x1, y1);
        point2 = Point(x2, y2);

        if (point2.y < point1.y)
        {
            Point::swap(point1, point2);
        }
        else if (point2.y == point1.y && point2.x < point1.x)
        {
            Point::swap(point1, point2);
        }
    }

    ~Crocodile() = default;

    void checkConnectionWithRiversides(double river_width, double jump_range)
    {
        if (point1.y <= jump_range)
            connected_to_start = 1;
        else if (river_width - point2.y <= jump_range)
            connected_to_finish = true;

        if (point2.y <= jump_range)
        {
            connected_to_start = 2;
            connection_with_start = new double[4];
        }
        else
            connection_with_start = new double[2];

        if (connected_to_start)
        {
            double temp = pow(jump_range, 2) - pow(point1.y, 2);
            temp = sqrt(temp);

            connection_with_start[0] = point1.x - temp;
            connection_with_start[1] = point1.x + temp;

            if (connected_to_start == 2)
            {
                temp = pow(jump_range, 2) - pow(point2.y, 2);
                temp = sqrt(temp);

                connection_with_start[2] = point2.x - temp;
                connection_with_start[3] = point2.x + temp;
            }
        }
    }

    void printConnections()
    {
        point1.print();
        std::cout << " ";
        point2.print();
        std::cout << " : ";

        if (connected_to_start)
            std::cout << "start < " << connection_with_start[0] << ", " << connection_with_start[1] << " > ";

        if (connected_to_start == 2)
            std::cout << "< " << connection_with_start[2] << ", " << connection_with_start[3] << " > ";

        if (connected_to_finish)
            std::cout << "finish ";
    }
};


#endif //CROCODILE_HPP
