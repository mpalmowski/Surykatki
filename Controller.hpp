#ifndef MODES_HPP
#define MODES_HPP

#include <exception>
#include "Generator.hpp"

int parameterError()
{
    std::cerr << "Invalid program parameters" << std::endl;
    std::cerr << "Proper use: ./surykatki <mode> <parameters> <<in_file >>out_file" << std::endl;
    return EXIT_FAILURE;
}

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
            throw std::invalid_argument("");

        std::string buf = argv[1];
        if (buf == "-m1")
            return m1();
        else if (buf == "-m2")
            return m2();
        else if (buf == "-m3")
            return m3();
        else if (buf == "-gen")
            return gen();
        else
            return parameterError();
    }

private:
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
                param_index = i;
                break;
            }
        }

        if (param_index > -1)
        {
            arg = argv[param_index];
            arg.erase(0, flag_str.length());
            ret_val = std::stoi(arg, nullptr);
        }
        else
            throw std::invalid_argument("");

        return ret_val;
    }

    int m1() //-m1
    {
        Solver *solver = nullptr;

        solver = BruteForce::readParametersAndCreate();
        solver->solve();
        solver->printFullResult();

        delete solver;

        return EXIT_SUCCESS;
    }

    int m2() //-m2 -n100
    {
        int nr_of_crocs;

        nr_of_crocs = getParam("-n");

        Generator generator(nr_of_crocs);
        generator.generate();

        Solver *solver = nullptr;
        solver = new BruteForce(nr_of_crocs, generator.real_river_length, generator.RIVER_WIDTH, generator.crocodiles);
        solver->solve();
        solver->printFullResult();

        delete solver;

        return EXIT_SUCCESS;
    }

    int m3() //-m3 n1000 -k30 -step500 -r10
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

                solver = new BruteForce(n, generator.real_river_length, generator.RIVER_WIDTH, generator.crocodiles);
                solver->solve(statistics);
                delete solver;
            }

            n += step;
            statistics.finishTrial();
        }
        statistics.print(nr_of_crocs, step, square);
        return EXIT_SUCCESS;
    }

    int gen() //-gen -n100
    {
        int nr_of_crocs = 0;

        nr_of_crocs = getParam("-n");

        Generator generator(nr_of_crocs);
        generator.generate();
        generator.print();

        return EXIT_SUCCESS;
    }

};

#endif
