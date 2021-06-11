#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main (int argv, char** argc)
{
    ImageProcessor imageProcessor;

    if (argv == 2)
    {
        std::string path(argc[1]);
        imageProcessor.execute(CommandLine("open " + path));
    }

    imageProcessor.start();

    return 0;
}