#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <exception>
#include "Raster.hpp"
#include "BruteForce.hpp"
#include "Generator.hpp"
#include <string>

void showManual()
{
    std::ifstream file("msg");
    std::string msg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::cout << msg;
}

typedef enum
{
    brute_force,
    raster
} Algorithm;

class Controller
{
public:
    Controller(int argc, char **argv) : argc(argc), argv(argv)
    {
        std_in_buf = std::cin.rdbuf();
        std_out_buf = std::cout.rdbuf();
        redirect();
    }

    ~Controller()
    {
        std::cin.rdbuf(std_in_buf);
        std::cout.rdbuf(std_out_buf);
    }

    int runApp()
    {
        if (argc < 2)
            throw std::invalid_argument("Not enough arguments.");

        std::string buf = argv[1];
        if (buf == "-m1")
            m1();
        else if (buf == "-m2")
            m2();
        else if (buf == "-m3")
            m3();
        else if (buf == "-gen")
            gen();
        else if (buf == "-help")
            showManual();
        else
            throw std::invalid_argument("Expected mode flag.");

        return EXIT_SUCCESS;
    }

private:
    const Algorithm algorithm = raster;
    std::streambuf *std_in_buf = nullptr;
    std::streambuf *std_out_buf = nullptr;
    std::ifstream in;
    std::ofstream out;
    int argc;
    char **argv;

    void redirect()
    {
        std::string buf;
        for (int i = 2; i < argc; ++i)
        {
            buf = argv[i];
            if (buf.find("<<") == 0)
            {
                buf.erase(0, 2);
                in.open(buf);
                std::cin.rdbuf(in.rdbuf());
            }
            else if (buf.find(">>") == 0)
            {
                buf.erase(0, 2);
                out.open(buf);
                std::cout.rdbuf(out.rdbuf());
            }
        }
    }

    int getParam(const char *flag)
    {
        std::string flag_str = flag;
        int ret_val;
        int param_index = -1;
        std::string arg;

        for (int i = 1; i < argc; ++i)
        {
            arg = argv[i];
            if (arg.find(flag) == 0)
            {
                if (param_index == -1)
                    param_index = i;
                else
                    param_index = -2;
            }
        }

        if (param_index > 0)
        {
            arg = argv[param_index];
            arg.erase(0, flag_str.length());
            ret_val = std::stoi(arg, nullptr);
        }
        else if (param_index == -1)
        {
            std::string msg = "Expected flag: ";
            msg += flag;
            throw std::invalid_argument(msg);
        }
        else
        {
            std::string msg = "Ambiguous flag: ";
            msg += flag;
            throw std::invalid_argument(msg);
        }

        return ret_val;
    }

    void m1() //-m1
    {
        Solver *solver = nullptr;

        switch (algorithm)
        {
            case brute_force:
                solver = BruteForce::readParametersAndCreate();
                break;
            case raster:
                solver = Raster::readParametersAndCreate();
                break;
        }
        solver->solve();
        solver->printFullResult();

        delete solver;
    }

    void m2() //-m2 -n100
    {
        int nr_of_crocs;

        nr_of_crocs = getParam("-n");

        Generator generator(nr_of_crocs);
        generator.generate();

        Solver *solver = nullptr;
        switch (algorithm)
        {
            case brute_force:
                solver = new BruteForce(nr_of_crocs, generator.real_river_length, generator.RIVER_WIDTH,
                                        generator.crocodiles);
                break;
            case raster:
                solver = new Raster(nr_of_crocs, generator.real_river_length, generator.RIVER_WIDTH,
                                    generator.crocodiles);
                break;
        }
        solver->solve();
        solver->printFullResult();

        delete solver;
    }

    void m3() //-m3 n1000 -k30 -step500 -r10
    {
        int nr_of_crocs, iters, step, repeats;

        nr_of_crocs = getParam("-n");
        iters = getParam("-k");
        step = getParam("-step");
        repeats = getParam("-r");

        Statistics statistics;
        Solver *solver = nullptr;
        int n = nr_of_crocs;
        for (int i = 0; i < iters; ++i)
        {
            statistics.newTrial();

            for (int j = 0; j < repeats; ++j)
            {
                Generator generator(n);
                generator.generate();

                switch (algorithm)
                {
                    case brute_force:
                        solver = new BruteForce(n, generator.real_river_length, generator.RIVER_WIDTH,
                                                generator.crocodiles);
                        break;
                    case raster:
                        solver = new Raster(n, generator.real_river_length, generator.RIVER_WIDTH,
                                            generator.crocodiles);
                        break;
                }

                solver->solve(statistics);
                delete solver;
            }

            n += step;
            statistics.finishTrial();
        }
        switch (algorithm)
        {
            case brute_force:
                statistics.print(nr_of_crocs, step, square);
                break;
            case raster:
                statistics.print(nr_of_crocs, step, linear);
                break;
        }
    }

    void gen() //-gen -n100
    {
        int nr_of_crocs = 0;

        nr_of_crocs = getParam("-n");

        Generator generator(nr_of_crocs);
        generator.generate();
        generator.print();
    }

};

#endif //CONTROLLER_HPP
