#ifndef RASTER_HPP
#define RASTER_HPP

#include "Solver.h"
#include <list>
#include <fstream>

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
            : Raster(nr_of_crocodiles, river_length, river_width, std::vector<Crocodile>()) {}

    Raster(const int nr_of_crocodiles, const double river_length, const double river_width,
           const std::vector<Crocodile> &crocodiles) : Solver(nr_of_crocodiles, river_length, river_width,
                                                              crocodiles)
    {
        createMap();
    }

    ~Raster() override
    {
        for (int i = 0; i < (int) (RIVER_LENGTH * RASTER_PRECISION); ++i)
        {
            delete[] pixel_map[i];
        }
        delete pixel_map;
    }

private:
    const double RASTER_PRECISION = 100.0;
    std::list<int> **pixel_map = nullptr;

    void findConnections() override
    {
        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            crocodiles[i].checkConnectionWithRiversides(RIVER_WIDTH, JUMP_RANGE);
        }

        checkConnections();
    }

    void createMap()
    {
        pixel_map = new std::list<int> *[(int) (RIVER_LENGTH * RASTER_PRECISION)];
        for (int i = 0; i < (int) (RIVER_LENGTH * RASTER_PRECISION); ++i)
        {
            pixel_map[i] = new std::list<int>[(int) (RIVER_WIDTH * RASTER_PRECISION)];
        }

        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            contour(crocodiles[i], i);
        }
        //testPrint();
    }

    int mapped(double coord)
    {
        return (int) round(coord * RASTER_PRECISION);
    }

    void addPixel(int x, int y, int index)
    {
        if (x >= 0 && y >= 0 && x < (int) (RIVER_LENGTH * RASTER_PRECISION) &&
            y < (int) (RIVER_WIDTH * RASTER_PRECISION))
        {
            if (pixel_map[x][y].empty() || pixel_map[x][y].back() != index)
                pixel_map[x][y].push_back(index);
        }
    }

    void contour(Crocodile &croc, int index)
    {
        midPoint(croc.point1, JUMP_RANGE / 2, index);
        midPoint(croc.point2, JUMP_RANGE / 2, index);

        double delta_x = croc.point2.x - croc.point1.x;
        double delta_y = croc.point2.y - croc.point1.y;
        double ratio = (JUMP_RANGE / 2) / croc.length;
        double new_x, new_y;

        new_x = croc.point1.x + delta_y * ratio;
        new_y = croc.point1.y + delta_x * -ratio;
        Point p1(new_x, new_y);
        new_x = croc.point2.x + delta_y * ratio;
        new_y = croc.point2.y + delta_x * -ratio;
        Point p2(new_x, new_y);
        bresenhamLine(p1, p2, index);

        new_x = croc.point1.x + delta_y * -ratio;
        new_y = croc.point1.y + delta_x * ratio;
        Point p3(new_x, new_y);
        new_x = croc.point2.x + delta_y * -ratio;
        new_y = croc.point2.y + delta_x * ratio;
        Point p4(new_x, new_y);
        bresenhamLine(p3, p4, index);
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

    void checkConnections()
    {
        for (int x = 0; x < (int) (RIVER_LENGTH * RASTER_PRECISION); ++x)
        {
            for (int y = 0; y < (int) (RIVER_WIDTH * RASTER_PRECISION); ++y)
            {
                for (auto const &index1 : pixel_map[x][y])
                {
                    for (auto const &index2 : pixel_map[x][y])
                    {
                        if (index1 != index2)
                        {
                            graph[index1][index2] = true;
                            graph[index2][index1] = true;
                        }
                    }
                }
            }
        }
    }

    void testPrint()
    {
        std::ofstream file;
        file.open("test.ppm");

        file << "P6" << "\n";
        file << (int) (RIVER_LENGTH * RASTER_PRECISION) << " ";
        file << (int) (RIVER_WIDTH * RASTER_PRECISION) << "\n";
        file << 255 << "\n";

        for (int y = 0; y < (int) (RIVER_WIDTH * RASTER_PRECISION); ++y)
        {
            for (int x = 0; x < (int) (RIVER_LENGTH * RASTER_PRECISION); ++x)
            {
                if (pixel_map[x][y].empty())
                    file << (char) 255 << (char) 255 << (char) 255;
                else
                {
                    auto color = (unsigned int) ((float) pixel_map[x][y].back() *
                                                 ((float) pow(255, 3) / (float) NR_OF_CROCODILES));

                    int r = color % 255;
                    color /= 255;
                    int g = color % 255;
                    color /= 255;
                    int b = color % 255;

                    file << (char) r << (char) g << (char) b;
                }
            }
        }
        file.close();
    }
};

#endif //RASTER_HPP
