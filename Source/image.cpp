#include "../Headers/image.h"
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>

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

void Image::print()
{
    std::cout << "Magic number: " << this->magicNumber << std::endl;
    std::cout << "Width: " << this->width << std::endl;
    std::cout << "Height: " << this->height << std::endl;
}

const char* Image::getMagicNumber() const
{
    return this->magicNumber;
}

unsigned int Image::getWidth() const
{
    return this->width;
}

unsigned int Image::getHeight() const
{
    return this->height;
}