#include "../Headers/image.h"
#include <cstring>
#include <stdexcept>
#include <fstream>

Image::Image(const char* magicNumber, unsigned int width, unsigned int height)
{
    if (strlen(magicNumber) != 2 || magicNumber[0] != 'P' || magicNumber[1] < '0' || magicNumber[1] > '9')
    {
        throw std::invalid_argument("Invalid magic number");
    }

    strcpy(this->magicNumber, magicNumber);
    this->magicNumber[2] = '\0';

    this->width = width;
    this->height = height;
}

bool Image::fileExists(std::string path)
{
    std::ifstream file(path.c_str());

    bool result = file.good();
    file.close();

    return result;
}