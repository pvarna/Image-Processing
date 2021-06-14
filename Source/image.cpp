#include "../Headers/image.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

Image::Image(ImageType type, unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels)
{
    if (type == ImageType::UNKNOWN)
    {
        throw std::invalid_argument("Invalid image type");
    }

    this->type = type;
    this->width = width;
    this->height = height;

    if (maxValue > DEFAULT_MAX_VALUE)
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

Image::Image(unsigned int width, unsigned int height, std::string hexCode)
{
    this->type = ImageType::PIXMAP;
    this->width = width;
    this->height = height;
    this->maxValue = DEFAULT_MAX_VALUE;

    std::size_t pixelsSize = width * height;

    for (std::size_t i = 0; i < pixelsSize; ++i)
    {
        this->pixels.push_back(RGB(hexCode));
    }
}

ImageType Image::getType() const
{
    return this->type;
}

unsigned int Image::getWidth() const
{
    return this->width;
}

unsigned int Image::getHeight() const
{
    return this->height;
}

unsigned int Image::getMaxValue() const
{
    return this->maxValue;
}

void Image::setType(ImageType type)
{
    this->type = type;
}

RGB& Image::operator [] (std::size_t index)
{
    if (index >= this->pixels.size())
    {
        throw std::overflow_error("Invalid index");
    }

    return this->pixels[index];
}