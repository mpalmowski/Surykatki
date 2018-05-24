#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "Crocodile.hpp"
#include "Point.hpp"
#include "Graph.hpp"
#include "Statistics.hpp"

const double JUMP_RANGE = 1.0;
const int NR_OF_MEERKATS = 5;

struct Path
{
    int start_node = 0;
    int finish_node = 0;
    int length = 0;

    Path(int start_node, int finish_node, int length) : start_node(start_node), finish_node(finish_node),
                                                        length(length) {}

    Path() = default;
};

class Solver
{
public:
    Solver(int nr_of_crocodiles, double river_length, double river_width,
           const std::vector<Crocodile> &crocodiles);

    Solver(int nr_of_crocodiles, double river_length, double river_width);

    virtual ~Solver();

    void solve();

    void solve(Statistics &statistics);

    void printFullResult();

protected:
    const int NR_OF_CROCODILES;
    const double RIVER_LENGTH;
    const double RIVER_WIDTH;
    std::vector<Crocodile> crocodiles;
    Graph *graph;
    double *meerkats = nullptr;
    std::vector<Path> shortest_paths;
    int *meerkat_routes = nullptr;

    void initCrocodiles();

    void sortCrocodiles();

    virtual void findConnections() {std::cout<<"base";}

    void calcMeerkatsDistances();

    void findPaths();

    void jumpAcrossRiver();

    static bool crocodileSorter(Crocodile croc1, Crocodile croc2);
};

#endif //SOLVER_H
