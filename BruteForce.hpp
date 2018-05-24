#ifndef BRUTE_FORCE_HPP
#define BRUTE_FORCE_HPP

#include "Solver.h"

class BruteForce : public Solver
{
public:
    static BruteForce *readParametersAndCreate()
    {
        int nr_of_crocodiles;
        double river_length;
        double river_width;
        std::cin >> nr_of_crocodiles;
        std::cin >> river_length;
        std::cin >> river_width;
        return new BruteForce(nr_of_crocodiles, river_length, river_width);
    }

    BruteForce(const int nr_of_crocodiles, const double river_length, const double river_width)
            : BruteForce(nr_of_crocodiles, river_length, river_width, std::vector<Crocodile>()) {}

    BruteForce(const int nr_of_crocodiles, const double river_length, const double river_width,
               const std::vector<Crocodile> &crocodiles) : Solver(nr_of_crocodiles, river_length, river_width,
                                                                    crocodiles) {}

    ~BruteForce() override = default;

private:

    void findConnections() override
    {
        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            crocodiles[i].checkConnectionWithRiversides(RIVER_WIDTH, JUMP_RANGE);

            for (int j = i + 1; j < NR_OF_CROCODILES; ++j)
            {
                if (!graph[i][j])
                {
                    if (checkConnection(crocodiles[i], crocodiles[j]))
                    {
                        graph[i][j] = 1;
                        graph[j][i] = 1;
                    }
                }
            }
        }
    }

    bool checkConnection(Crocodile &croc1, Crocodile &croc2)
    {
        double u;

        u = pointOfIntersection(croc1.point2, croc2);
        if (calcDistance(croc1.point2, u, croc2) <= JUMP_RANGE)
            return true;

        u = pointOfIntersection(croc2.point1, croc1);
        if (calcDistance(croc2.point1, u, croc1) <= JUMP_RANGE)
            return true;

        u = pointOfIntersection(croc1.point1, croc2);
        if (calcDistance(croc1.point1, u, croc2) <= JUMP_RANGE)
            return true;

        u = pointOfIntersection(croc2.point2, croc1);
        return calcDistance(croc2.point2, u, croc1) <= JUMP_RANGE;
    }

    double pointOfIntersection(Point point, Crocodile &croc)
    {
        double u;

        u = (point.x - croc.point1.x) * (croc.point2.x - croc.point1.x) +
            (point.y - croc.point1.y) * (croc.point2.y - croc.point1.y);
        u /= croc.length_pow;

        return u;
    }

    double calcDistance(Point point, double u, Crocodile &croc)
    {
        double distance;
        double xi, yi;

        if (u < 0)
            u = 0;

        if (u > 1)
            u = 1;

        xi = croc.point1.x + u * (croc.point2.x - croc.point1.x);
        yi = croc.point1.y + u * (croc.point2.y - croc.point1.y);

        distance = pow((point.x - xi), 2) + pow((point.y - yi), 2);
        distance = sqrt(distance);

        return distance;
    }
};

#endif //BRUTE_FORCE_HPP
