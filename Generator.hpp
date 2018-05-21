#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <cmath>
#include "Crocodile.hpp"
#include <vector>

const double CROC_MAX_LENGTH = 2.0;
const double CROC_MIN_LENGTH = 0.5;
const double WIDTH_ASPECT = 0.5;
const double LENGTH_ASPECT = 2;

double doubleRand()
{
    return (double) rand() / (double) RAND_MAX;
}

struct Generator
{
    const int NR_OF_CROCS;
    const double RIVER_WIDTH;
    const double RIVER_LENGTH;
    double real_river_length = 0;
    std::vector<Crocodile> crocodiles;

    explicit Generator(const int nr_of_crocodiles) : NR_OF_CROCS(nr_of_crocodiles),
                                                     RIVER_WIDTH(sqrt(double(NR_OF_CROCS)) * WIDTH_ASPECT * CROC_MAX_LENGTH),
                                                     RIVER_LENGTH(RIVER_WIDTH * LENGTH_ASPECT) {}

    void generate()
    {
        srand((unsigned int) (time(nullptr)));
        real_river_length = RIVER_LENGTH + 2 * CROC_MAX_LENGTH;
        for (int i = 0; i < NR_OF_CROCS; ++i)
        {
            double x1 = doubleRand() * RIVER_LENGTH;
            double y1 = doubleRand() * RIVER_WIDTH;

            double alpha_start = 0, alpha_max = M_PI * 2;
            double crocodile_length =
                    CROC_MIN_LENGTH + doubleRand() * (CROC_MAX_LENGTH - CROC_MIN_LENGTH);
            if (y1 + crocodile_length > RIVER_WIDTH)
            {
                double distance_from_coast = RIVER_WIDTH - y1;
                double x2_min = x1 - sqrt(pow(crocodile_length, 2) - pow(distance_from_coast, 2));
                double sin_beta = (x1 - x2_min) / crocodile_length;
                double alpha_temp = asin(sin_beta);
                alpha_start = M_PI / 2 + alpha_temp;
                alpha_max = M_PI * 2 - 2 * alpha_temp;
            }
            else if (y1 - crocodile_length < 0)
            {
                double distance_from_coast = y1;
                double x2_min = x1 - sqrt(pow(crocodile_length, 2) - pow(distance_from_coast, 2));
                double sin_beta = (x1 - x2_min) / crocodile_length;
                double alpha_temp = asin(sin_beta);
                alpha_start = 3 * M_PI / 2 + alpha_temp;
                alpha_max = M_PI * 2 - 2 * alpha_temp;
            }
            double alpha = alpha_start + doubleRand() * alpha_max;
            if (alpha >= M_PI * 2)
                alpha -= M_PI * 2;
            double x2 = crocodile_length * cos(alpha) + x1;
            double y2 = crocodile_length * sin(alpha) + y1;

            x1 += CROC_MAX_LENGTH;
            x2 += CROC_MAX_LENGTH;

            crocodiles.emplace_back(x1, y1, x2, y2, crocodile_length);
        }
    }

    void print()
    {
        const std::string endl = "\r\n";
        std::cout << NR_OF_CROCS << " " << real_river_length << " " << RIVER_WIDTH << endl;
        for(int i = 0; i < NR_OF_CROCS; ++i)
        {
            std::cout << crocodiles[i].point1.x << " ";
            std::cout << crocodiles[i].point1.y << " ";
            std::cout << crocodiles[i].point2.x << " ";
            std::cout << crocodiles[i].point2.y << " ";
            std::cout << crocodiles[i].length << endl;
        }
    }
};

#endif //GENERATOR_HPP
