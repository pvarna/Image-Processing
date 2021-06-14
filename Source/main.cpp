#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main (int argv, char** argc)
{
    if (argv == 2)
    {
        std::string path(argc[1]);
        try
        {
            ImageProcessor::getInstance().execute(CommandLine("open " + path));
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        
    }

    ImageProcessor::getInstance().start();

    return 0;
}