#pragma once

#include "consts.h"
#include <string>


class Image
{
protected:
    char magicNumber[MAGIC_NUMBER_LENGHT + 1];
    unsigned int width;
    unsigned int height;

    Image(const char* magicNumber, unsigned int width, unsigned int height);

public:
    virtual void print();
    //virtual void write(std::string path) = 0;
    //virtual ~Image() = default;

    const char* getMagicNumber() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;

    virtual ~Image();
};