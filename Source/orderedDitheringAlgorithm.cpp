#include "../Headers/orderedDitheringAlgorithm.h"
#include <iostream>

OrderedDitheringAlgorithm::OrderedDitheringAlgorithm(Image* image, int table[MAX_TABLE_SIDE][MAX_TABLE_SIDE], int tableSide, int divisor)
{
    this->image = image;
    for (std::size_t i = 0; i < MAX_TABLE_SIDE; ++i)
    {
        for (std::size_t j = 0; j < MAX_TABLE_SIDE; ++j)
        {
            this->table[i][j] = table[i][j];
        }
    }
    this->tableSide = tableSide;
    this->divisor = divisor;
    this->loadGrayscalePixels();
}

int OrderedDitheringAlgorithm::RGBToGrayscale(RGB color)
{
    int max = std::max(color.red, std::max(color.green, color.blue));
    int min = std::min(color.red, std::min(color.green, color.blue));

    return static_cast<int>((static_cast<double>(min) + static_cast<double>(max)) / 2);
}

void OrderedDitheringAlgorithm::loadGrayscalePixels()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();

    for (std::size_t i = 0; i < width * height; ++i)
    {
        this->grayscalePixels.push_back(this->RGBToGrayscale((*this->image)[i]));
    }
}

Image* OrderedDitheringAlgorithm::dither()
{
    std::vector<RGB> newPixels;
    ImageType type = this->image->getType();
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    for (std::size_t i = 0; i < height; ++i)
    {
        int row = i % this->tableSide;
        for (std::size_t j = 0; j < width; ++j)
        {
            int column = j % this->tableSide;
            int oldPixel = this->grayscalePixels[i*width + j];
            int newPixel;
            
            if ((oldPixel >> this->divisor) < this->table[row][column])
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels); 
}