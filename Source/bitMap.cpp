#include "../Headers/bitMap.h"
#include <stdexcept>

BitMap::BitMap(unsigned int width, unsigned int height, std::vector<bool> pixels)
    : Image("P1", width, height)
{
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