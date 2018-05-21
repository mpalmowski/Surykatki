#include <iostream>
#include <fstream>
#include "BruteForce.h"
#include "Controller.hpp"

std::string loadErrorMessage()
{
    std::ifstream file("msg");
    std::string msg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return msg;
}

int main(int argc, char **argv)
{
    std::string errorMsg = loadErrorMessage();

    try
    {
        Controller controller(argc, argv);
        return controller.runApp();
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        std::cout << errorMsg;
        return EXIT_FAILURE;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }
}