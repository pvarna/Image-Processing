#include "../Headers/grayMap.h"
#include <stdexcept>
#include <cstddef>
#include <fstream>
#include <iostream>

const std::size_t DEFAULT_MAX_VALUE = 255;

GrayMap::GrayMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<unsigned int> pixels)
    : Image("P2", width, height)
{
    if (this->maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Invalid max value");
    }

    this->maxValue = maxValue;

    std::size_t pixelsSize = pixels.size();

    if (pixelsSize != width * height)
    {
        throw std::invalid_argument("Invalid number of pixels");
    }

    for (std::size_t i = 0; i < pixelsSize; ++i)
    {
        this->pixels.push_back(pixels[i]);
    }
}