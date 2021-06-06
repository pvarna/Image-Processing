#pragma once

#include "consts.h"
#include "rgb.h"
#include "enums.h"
#include <vector>
#include <string>

class Image
{
protected:
    ImageType type;
    unsigned int width;
    unsigned int height;
    unsigned int maxValue;
    std::vector<RGB> pixels;

public:
    Image(ImageType type, unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels);
    Image(unsigned int width, unsigned int height, std::string hexCode);

    ImageType getType() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getMaxValue() const;

    RGB operator [] (std::size_t index) const;

    //virtual ~Image();
};