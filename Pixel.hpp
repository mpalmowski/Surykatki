#ifndef PIXEL_HPP
#define PIXEL_HPP

template<class Type>
class Pixel
{
public:
    Pixel()
    {
        data = new Type[0];
    }

    ~Pixel()
    {
        delete data;
    }

    int getSize()
    {
        return size;
    }

    Type *getData()
    {
        return data;
    }

    void add(Type value)
    {
        if (find(value))
            return;

        expandStorage();
        data[size - 1] = value;
    }

private:
    Type *data = nullptr;
    int size = 0;

    bool find(Type value)
    {
        for (int i = 0; i < size; ++i)
        {
            if (data[i] == value)
                return true;
        }
        return false;
    }

    void expandStorage()
    {
        Type *temp = new Type[size + 1];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = data[i];
        }
        delete data;
        data = temp;
        size++;
    }
};

#endif //PIXEL_HPP
