#ifndef PIXELMAP_HPP
#define PIXELMAP_HPP

#include "UniqueSet.hpp"

template<class Type>
class PixelMap
{
public:
    PixelMap(int width, int height) : WIDTH(width), HEIGHT(height)
    {
        map = new UniqueSet<Type> **[WIDTH];
        for(int i = 0; i < WIDTH; ++i)
            map[i] = new UniqueSet<Type> *[HEIGHT];

        for(int i = 0; i < WIDTH; ++i)
            for(int j = 0; j < HEIGHT; ++j)
                map[i][j] = nullptr;
    }

    ~PixelMap()
    {
        for(int i = 0; i < WIDTH; ++i)
            for(int j = 0; j < HEIGHT; ++j)
                delete map[i][j];

        for(int i = 0; i < WIDTH; ++i)
            delete[] map[i];

        delete[] map;
    }

    void putPixel(int x, int y, Type value)
    {
        if (map[x][y] == nullptr)
            map[x][y] = new UniqueSet<Type>;

        map[x][y]->add(value);

        Type *data = map[x][y]->getData();
        int size = map[x][y]->getSize();
    }

    UniqueSet<Type> *getPixel(int x, int y)
    {
        return map[x][y];
    }

private:
    const int WIDTH, HEIGHT;
    UniqueSet<Type> ***map;
};

#endif //PIXELMAP_HPP
