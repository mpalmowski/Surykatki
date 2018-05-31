#ifndef RASTER_HPP
#define RASTER_HPP

#include "Solver.h"
#include "PixelMap.hpp"
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
            : Solver(nr_of_crocodiles, river_length, river_width)
    {}

    Raster(const int nr_of_crocodiles, const double river_length, const double river_width,
           const std::vector<Crocodile> &crocodiles) : Solver(nr_of_crocodiles, river_length, river_width,
                                                              crocodiles)
    {}

    ~Raster() override
    {
        delete pixel_map;
    }

private:
    const double RASTER_PRECISION = 100.0;
    int map_width = 0, map_height = 0;
    PixelMap<int> *pixel_map = nullptr;

    void findConnections() override
    {
        createMap();
        for (int i = 0; i < NR_OF_CROCODILES; ++i)
        {
            crocodiles[i].checkConnectionWithRiversides(RIVER_WIDTH, JUMP_RANGE);
        }

        checkConnections();
    }

    void createMap()
    {
        map_width = (int) (RIVER_LENGTH * RASTER_PRECISION);
        map_height = (int) (RIVER_WIDTH * RASTER_PRECISION);

        pixel_map = new PixelMap<int>(map_width, map_height);

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
        if (x >= 0 && y >= 0 && x < map_width &&
            y < map_height)
        {
            pixel_map->putPixel(x, y, index);
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
        for (int x = 0; x < map_width; ++x)
        {
            for (int y = 0; y < map_height; ++y)
            {
                auto pixel = pixel_map->getPixel(x, y);
                if (pixel == nullptr)
                    continue;
                int *pixel_data = pixel->getData();
                int size = pixel->getSize();
                for (int i = 0; i < size; ++i)
                {
                    for (int j = 0; j < size; ++j)
                    {
                        if (pixel_data[i] != pixel_data[j])
                        {
                            graph->node(pixel_data[i], pixel_data[j]) = 1;
                            graph->node(pixel_data[j], pixel_data[i]) = 1;
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
        file << map_width << " ";
        file << map_height << "\n";
        file << 255 << "\n";

        const int colors_skipped = 150;
        const double nr_of_colors = pow(256, 3) - 1 - colors_skipped;
        const double normal = nr_of_colors / (NR_OF_CROCODILES - 1);

        for (int y = map_height - 1; y >= 0; --y)
        {
            for (int x = 0; x < map_width; ++x)
            {
                UniqueSet<int> *pixel = pixel_map->getPixel(x, y);
                if (pixel == nullptr)
                    file << (char) 255 << (char) 255 << (char) 255;
                else
                {
                    auto pixel_data = pixel->getData();
                    auto color = (unsigned int) (pixel_data[0] * normal);

                    color += 1;
                    int b = color % 256;
                    color /= 256;
                    int g = color % 256;
                    color /= 256;
                    int r = color % 256;

                    file << (char) r << (char) g << (char) b;
                }
            }
        }
        file.close();
    }
};

#endif //RASTER_HPP
