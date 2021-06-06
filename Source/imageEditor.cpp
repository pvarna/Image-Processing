#include "../Headers/imageEditor.h"
#include "../Headers/rgb.h"
#include "../Headers/enums.h"
#include <stdexcept>
#include <vector>

ImageEditor::ImageEditor(Image* image)
{
    if (!image)
    {
        throw std::invalid_argument("No image is loaded");
    }

    this->toBeEdited = image;
}

inline bool ImageEditor::isCloserToZero(int value, int maxValue)
{
    return value < (maxValue - value);
}

Image* ImageEditor::oneDimensionalErrorDiffusion()
{
    std::vector<RGB> newPixels;
    ImageType type = this->toBeEdited->getType();
    unsigned int width = this->toBeEdited->getWidth();
    unsigned int height = this->toBeEdited->getHeight();
    unsigned int maxValue = this->toBeEdited->getMaxValue();

    for (std::size_t i = 0; i < height; ++i)
    {
        int error = 0;
        for (std::size_t j = 0; j < width; ++j)
        {
            unsigned int averagePixel = ((*this->toBeEdited)[i*width + j].red +
                                         (*this->toBeEdited)[i*width + j].green +
                                         (*this->toBeEdited)[i*width + j].blue) / 3;
            unsigned int newPixel;

            if (isCloserToZero(averagePixel + error, maxValue))
            {
                newPixel = 0;
                error += averagePixel;
            }
            else
            {
                newPixel = maxValue;
                error += averagePixel - maxValue;
            }

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::twoDimensionalErrorDiffusion()
{
    std::vector<RGB> newPixels;
    ImageType type = this->toBeEdited->getType();
    unsigned int width = this->toBeEdited->getWidth();
    unsigned int height = this->toBeEdited->getHeight();
    unsigned int maxValue = this->toBeEdited->getMaxValue();

    std::vector<unsigned int> errorsPreviousLine;
    for (std::size_t i = 0; i < width; ++i)
    {
        errorsPreviousLine.push_back(0);
    }

    for (std::size_t i = 0; i < height; ++i)
    {
        int errorToNextPixel = 0;
        for (std::size_t j = 0; j < width; ++j)
        {
            unsigned int averagePixel = ((*this->toBeEdited)[i*width + j].red +
                                         (*this->toBeEdited)[i*width + j].green +
                                         (*this->toBeEdited)[i*width + j].blue) / 3;
            unsigned int newPixel;

            if (isCloserToZero(averagePixel + errorToNextPixel/2 + errorsPreviousLine[j]/2, maxValue))
            {
                newPixel = 0;
                errorToNextPixel += averagePixel;
            }
            else
            {
                newPixel = maxValue;
                errorToNextPixel += averagePixel - maxValue;
            }

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}