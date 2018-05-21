#include <iostream>
#include <fstream>
#include "BruteForce.h"
#include "Controller.hpp"

int main(int argc, char **argv)
{
    try
    {
        Controller controller(argc, argv);
        return controller.runApp();
    }
    catch (std::invalid_argument &e)
    {
        return parameterError();
    }
    catch (std::exception &e)
    {
        std::cerr<<e.what();
        return EXIT_FAILURE;
    }
}