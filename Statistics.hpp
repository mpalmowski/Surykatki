#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <chrono>
#include <vector>
#include <iostream>
#include <cmath>

typedef enum
{
    linear = 1,
    square = 2,
    cubic = 3
} Complexity;

class Statistics
{
public:

    Statistics() = default;

    void newTrial()
    {
        if (!times.empty())
            finishTrial();
        trials.push_back(0);
    }

    void finishTrial()
    {
        unsigned long nr_of_elements = times.size();
        long double average = 0;
        for (int i = 0; i < nr_of_elements; ++i)
        {
            average += times[i] / (long double) nr_of_elements;
        }
        times.clear();

        trials[trials.size() - 1] = average;
    }

    void start()
    {
        begin = std::chrono::high_resolution_clock::now();
    }

    void stop()
    {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<long double> duration = end - begin;
        times.push_back(duration.count());
    }

    void print(int init_n, int step, Complexity complexity)
    {
        std::cout << "n;t(n);T(n);q(n)" << "\r\n";

        long double *estimated_times;
        estimated_times = new long double[trials.size()];
        for (int i = 0; i < trials.size(); ++i)
        {
            estimated_times[i] = init_n + i * step;
            estimated_times[i] = pow(estimated_times[i], complexity);
            estimated_times[i] /= 1000;
        }

        int n = init_n;
        long double q = 0;
        for (int i = 0; i < trials.size(); ++i)
        {
            q = (trials[i] * estimated_times[trials.size() / 2]) / (estimated_times[i] * trials[trials.size() / 2]);

            std::cout << n << ";" << trials[i] * 1000 << ";" << estimated_times[i] << ";" << q << "\r\n";

            n += step;
        }
        delete estimated_times;
    }

private:
    std::chrono::high_resolution_clock::time_point begin, end;
    std::vector<long double> trials;
    std::vector<long double> times;
};

#endif //STATISTICS_HPP
