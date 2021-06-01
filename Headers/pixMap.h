#pragma once

#include "image.h"
#include "rgb.h"
#include <vector>
#include <string>

const std::size_t DEFAULT_MAX_VALUE = 255;

class PixMap : public Image
{
private:
    unsigned int maxValue;
    std::vector<RGB> pixels;

    //bool fileExists(std::string path);

public:
    PixMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels);
    PixMap(unsigned int width, unsigned int height, std::string hexCode);
};