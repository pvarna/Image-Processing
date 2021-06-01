#pragma once

#include <cstddef>
#include <string>

const std::size_t MAGIC_NUMBER_LENGHT = 2;

class Image
{
protected:
    char magicNumber[MAGIC_NUMBER_LENGHT + 1];
    unsigned int width;
    unsigned int height;

    bool fileExists(std::string path);

    Image(const char* magicNumber, unsigned int width, unsigned int height);
public:

};