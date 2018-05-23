#ifndef RASTER_HPP
#define RASTER_HPP

#include "Solver.h"
#include <queue>

class Raster : public Solver
{
public:
    static Raster *readParametersAndCreate()
    {
        int nr_of_crocodiles;
        double river_length;
        double river_width;
        std::cin >> nr_of_crocodiles;
        std::cin >> river_length;
        std::cin >> river_width;
        return new Raster(nr_of_crocodiles, river_length, river_width);
    }

    Raster(const int nr_of_crocodiles, const double river_length, const double river_width)
            : Solver(nr_of_crocodiles, river_length, river_width) {}

    Raster(const int nr_of_crocodiles, const double river_length, const double river_width,
           const std::vector<Crocodile> &crocodiles) : Solver(nr_of_crocodiles, river_length, river_width,
                                                              crocodiles) {}

    ~Raster() override = default;

private:
    const double RASTER_PRECISION = 100.0;
    std::queue<int> **pixel_map = nullptr;

    void findConnections() override
    {
        createMap();

        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            crocodiles[i].checkConnectionWithRiversides(RIVER_WIDTH, JUMP_RANGE);

            for (int j = i + 1; j < NR_OF_CROCODILES; ++j)
            {
                checkConnections(crocodiles[i]);
            }
        }
    }

    void createMap()
    {
        pixel_map = new std::queue<int> *[(int) (RIVER_LENGTH * RASTER_PRECISION)];
        for (int i = 0; i < RIVER_LENGTH * RASTER_PRECISION; ++i)
        {
            pixel_map[i] = new std::queue<int>[(int) (RIVER_WIDTH * RASTER_PRECISION)];
        }

        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            bresenhamLine(crocodiles[i].point1, crocodiles[i].point2, i);
        }
    }

    void bresenhamLine(Point p1, Point p2, int index)
    {
        int x1 = mapped(p1.x);
        int y1 = mapped(p1.y);
        int x2 = mapped(p2.x);
        int y2 = mapped(p2.y);

        int delta_x = x2 - x1;
        int delta_y = y2 - y1;
        auto steps = std::max(abs(delta_x), abs(delta_y));

        double x_inc = (double) delta_x / (double) steps;
        double y_inc = (double) delta_y / (double) steps;

        double x = x1, y = y1;
        addPixel((int) x, (int) y, index);

        for (int i = 0; i < steps; ++i)
        {
            x += x_inc;
            y += y_inc;
            addPixel((int) round(x), (int) round(y), index);
        }
    }

    int mapped(double coord)
    {
        return (int) round(coord * RASTER_PRECISION);
    }

    void addPixel(int x, int y, int index)
    {
        if (pixel_map[x][y].empty() || pixel_map[x][y].back() != index)
            pixel_map[x][y].push(index);
    }

    void midPoint(Point middle, double radius, int index)
    {
        int x0 = mapped(middle.x);
        int y0 = mapped(middle.y);
        int x = mapped(radius);
        int y = 0;
        int err = 0;
        while (x >= y)
        {
            addPixel(x0 + x, y0 + y, index);
            addPixel(x0 + y, y0 + x, index);
            addPixel(x0 - x, y0 + y, index);
            addPixel(x0 - y, y0 + x, index);
            addPixel(x0 - x, y0 - y, index);
            addPixel(x0 - y, y0 - x, index);
            addPixel(x0 + x, y0 - y, index);
            addPixel(x0 + y, y0 - x, index);

            if (err <= 0)
            {
                y += 1;
                err += 2 * y + 1;
            }

            if (err > 0)
            {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
    }

    void checkConnections(Crocodile &croc1)
    {

    }
};

#endif //RASTER_HPP
