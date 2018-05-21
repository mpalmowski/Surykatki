#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "Solver.h"

class BruteForce : public Solver
{
public:
    static BruteForce *readParametersAndCreate();

    BruteForce(const int nr_of_crocodiles, const double river_length, const double river_width)
            : Solver(nr_of_crocodiles, river_length, river_width) {}

    BruteForce(const int nr_of_crocodiles, const double river_length, const double river_width,
               const std::vector<Crocodile> &crocodiles) : Solver(nr_of_crocodiles, river_length, river_width,
                                                                    crocodiles) {}

    ~BruteForce() override = default;

private:

    void findConnections() override;

    bool checkConnection(Crocodile &croc1, Crocodile &croc2);

    double pointOfIntersection(Point point, Crocodile &croc);

    double calcDistance(Point point, double u, Crocodile &croc);
};

#endif //BRUTE_FORCE_H
