#pragma once

#include "image.h"
#include <vector>

class BitMap : public Image
{
private:
    std::vector<bool> pixels;

public:
    BitMap(unsigned int width, unsigned int height, std::vector<bool> pixels);
};