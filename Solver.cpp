#include "Solver.h"
#include "Statistics.hpp"

Solver::Solver(const int nr_of_crocodiles, const double river_length, const double river_width,
               const std::vector<Crocodile> &crocodiles) : NR_OF_CROCODILES(nr_of_crocodiles),
                                                           RIVER_LENGTH(river_length), RIVER_WIDTH(river_width),
                                                           crocodiles(crocodiles)
{
    graph = Graph(nr_of_crocodiles + NR_OF_MEERKATS, nr_of_crocodiles);

    for (int i = 0; i < graph.lines; ++i)
        for (int j = 0; j < graph.columns; ++j)
            graph[i][j] = 0;

    meerkats = new double[NR_OF_MEERKATS];
    for (int i = 0; i < NR_OF_MEERKATS; ++i)
    {
        meerkats[i] = (i + 1) * river_length / (NR_OF_MEERKATS + 1);
    }

    meerkat_routes = new int[NR_OF_MEERKATS];
    for (int i = 0; i < NR_OF_MEERKATS; ++i)
    {
        meerkat_routes[i] = 0;
    }

    sortCrocodiles();
}

Solver::Solver(int nr_of_crocodiles, double river_length, double river_width) : Solver(nr_of_crocodiles, river_length,
                                                                                       river_width,
                                                                                       std::vector<Crocodile>())
{
    initCrocodiles();
    sortCrocodiles();
}

Solver::~Solver()
{
    delete meerkats;

    delete meerkat_routes;
}

void Solver::solve()
{
    findConnections();

    calcMeerkatsDistances();

    findPaths();

    jumpAcrossRiver();
}

void Solver::solve(Statistics &statistics)
{
    statistics.start();

    solve();

    statistics.stop();
}

void Solver::printFullResult()
{
    if (meerkat_routes[0] == 0)
    {
        std::cout << "No possible way found to cross the river" << std::endl;
        return;
    }

    for (int i = 0; i < NR_OF_CROCODILES; ++i)
    {
        std::cout << "Crocodile[" << i << "] ";
        crocodiles[i].printConnections();
        for (int j = 0; j < NR_OF_CROCODILES; ++j)
        {
            if (graph[i][j] != 0)
                std::cout << j << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < NR_OF_MEERKATS; ++i)
    {
        std::cout << "Meerkat[" << i << "] ( " << meerkats[i] << " ): ";
        for (int j = 0; j < NR_OF_CROCODILES; ++j)
        {
            if (graph[i + NR_OF_CROCODILES][j] != 0)
                std::cout << j << "(" << graph[i + NR_OF_CROCODILES][j] << ") ";
        }
        std::cout << std::endl;
    }

    for (auto &shortest_path : shortest_paths)
        std::cout << shortest_path.start_node << " -> " << shortest_path.finish_node << " "
                  << shortest_path.length << std::endl;

    for (int i = 0; i < NR_OF_MEERKATS; ++i)
        std::cout << "Meerkat[" << i << "] crossed the river in " << meerkat_routes[i] << " jumps" << std::endl;
}

void Solver::initCrocodiles()
{
    double x1, y1, x2, y2, length;
    for (int i = 0; i < NR_OF_CROCODILES; ++i)
    {
        std::cin >> x1;
        std::cin >> y1;
        std::cin >> x2;
        std::cin >> y2;
        std::cin >> length;
        crocodiles.emplace_back(x1, y1, x2, y2, length);
    }
}

void Solver::sortCrocodiles()
{
    std::stable_sort(crocodiles.begin(), crocodiles.end(), crocodileSorter);
}

void Solver::calcMeerkatsDistances()
{
    int distance, temp_dist;

    for (int i = 0; i < NR_OF_MEERKATS; ++i)
    {
        for (int j = 0; j < NR_OF_CROCODILES; ++j)
        {
            if (crocodiles[j].connected_to_start == 0)
                continue;

            distance = std::numeric_limits<int>::max();

            for (int k = 0; k < crocodiles[j].connected_to_start * 2; ++k)
            {
                temp_dist = (int) std::ceil(fabs(crocodiles[j].connection_with_start[k] - meerkats[i]) / JUMP_RANGE);
                if (temp_dist < distance)
                    distance = temp_dist;
            }

            if (crocodiles[j].connected_to_start >= 1)
                if (meerkats[i] >= crocodiles[j].connection_with_start[0] &&
                    meerkats[i] <= crocodiles[j].connection_with_start[1])
                    distance = 0;

            if (crocodiles[j].connected_to_start == 2)
                if (meerkats[i] >= crocodiles[j].connection_with_start[2] &&
                    meerkats[i] <= crocodiles[j].connection_with_start[3])
                    distance = 0;

            graph[NR_OF_CROCODILES + i][j] = distance + 1;
        }
    }
}

void Solver::findPaths()
{
    Path temp_path, shortest_path;

    graph.updatePaths();

    for (int i = 0; i < NR_OF_CROCODILES; ++i)
    {
        if (crocodiles[i].connected_to_start == 0)
            continue;

        graph.BreadthFirstSearch(i);

        shortest_path = Path(i, i, 0);

        for (int j = 0; j < NR_OF_CROCODILES; ++j)
        {
            if (crocodiles[j].connected_to_finish == 0)
                continue;

            auto distance = graph.getDistance(i, j);
            if (distance != 0)
            {
                temp_path = Path(i, j, distance);

                if (temp_path.length < shortest_path.length || shortest_path.length == 0)
                    shortest_path = temp_path;
            }
        }

        shortest_paths.push_back(shortest_path);
    }
}

void Solver::jumpAcrossRiver()
{
    int distance, temp_distance;
    for (int i = 0; i < NR_OF_MEERKATS; ++i)
    {
        distance = 0;

        for (int j = 0; j < NR_OF_CROCODILES; ++j)
        {
            if (graph[i + NR_OF_CROCODILES][j] == 0 || shortest_paths[j].length == 0)
                continue;

            temp_distance = graph[i + NR_OF_CROCODILES][j] + shortest_paths[j].length;

            if (temp_distance < distance || distance == 0)
                distance = temp_distance;
        }

        meerkat_routes[i] = distance;
    }
}

bool Solver::crocodileSorter(Crocodile croc1, Crocodile croc2)
{
    if (croc1.point1.y < croc2.point1.y)
        return true;
    else if (croc1.point1.y == croc2.point1.y && croc1.point2.y < croc2.point2.y)
        return true;
    return false;
}
