#pragma once

#include "image.h"
#include <vector>

class GrayMap : public Image
{
private:
    unsigned int maxValue;
    std::vector<unsigned int> pixels;

public:
    GrayMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<unsigned int> pixels);
};