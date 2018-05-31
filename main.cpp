#include <iostream>
#include <fstream>
#include "Controller.hpp"

int main(int argc, char **argv)
{
    try
    {
        Controller controller(argc, argv);
        controller.runApp();
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
        showManual();
        return EXIT_FAILURE;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}