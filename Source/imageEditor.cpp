#include "../Headers/imageEditor.h"
#include "../Headers/rgb.h"
#include "../Headers/enums.h"
#include <stdexcept>
#include <vector>
#include <iostream>

ImageEditor::ImageEditor(Image* image)
{
    if (!image)
    {
        throw std::invalid_argument("No image is loaded");
    }

    this->toBeEdited = image;

    unsigned int width = this->toBeEdited->getWidth();
    unsigned int height = this->toBeEdited->getHeight();
    for (std::size_t i = 0; i < height; ++i)
    {
        for (std::size_t j = 0; j < width; ++j)
        {
            int max = std::max((*this->toBeEdited)[i*width + j].red, std::max((*this->toBeEdited)[i*width + j].green, (*this->toBeEdited)[i*width + j].blue));
            int min = std::min((*this->toBeEdited)[i*width + j].red, std::min((*this->toBeEdited)[i*width + j].green, (*this->toBeEdited)[i*width + j].blue));
            this->averagePixels.push_back((min+max)/2);
        }
    }
}

inline bool ImageEditor::isCloserToZero(int value, int maxValue)
{
    return value < (maxValue - value);
}

inline bool ImageEditor::isInsideTheImage(std::size_t i, std::size_t j, unsigned int height, unsigned int width)
{
    return i < height && j < width;
}

void ImageEditor::getCoefficientTable(ErrorDiffusionAlrogithm algorithm, int coefficients[3][5], 
                                        bool& isShiftable, int& divisor)
{
    switch (algorithm)
    {
    case ErrorDiffusionAlrogithm::BASIC_ONE_DIMENSIONAL:
        coefficients[0][3] = 1;
        isShiftable = false;
        divisor = 1;
        break;

    case ErrorDiffusionAlrogithm::BASIC_TWO_DIMENSIONAL:
        coefficients[0][3] = 1;
        coefficients[1][2] = 1;
        isShiftable = true;
        divisor = 1;
        break;

    case ErrorDiffusionAlrogithm::FLOYD_STEINBERG:
        coefficients[0][3] = 7;
        coefficients[1][1] = 3;
        coefficients[1][2] = 5;
        coefficients[1][3] = 1;
        isShiftable = true;
        divisor = 4;
        break;

    case ErrorDiffusionAlrogithm::FLOYD_STEINBERG_FALSE:
        coefficients[0][3] = 3;
        coefficients[1][2] = 3;
        coefficients[1][3] = 2;
        isShiftable = true;
        divisor = 3;
        break;

    case ErrorDiffusionAlrogithm::JARVIS_JUDICE_NINKE:
        coefficients[0][3] = 7;
        coefficients[0][4] = 5;
        coefficients[1][0] = 3;
        coefficients[1][1] = 5;
        coefficients[1][2] = 7;
        coefficients[1][3] = 5;
        coefficients[1][4] = 3;
        coefficients[2][0] = 1;
        coefficients[2][1] = 3;
        coefficients[2][2] = 5;
        coefficients[2][3] = 3;
        coefficients[2][4] = 1;
        isShiftable = false;
        divisor = 48;
        break;

    case ErrorDiffusionAlrogithm::STUCKI:
        coefficients[0][3] = 8;
        coefficients[0][4] = 4;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 8;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        coefficients[2][0] = 1;
        coefficients[2][1] = 2;
        coefficients[2][2] = 4;
        coefficients[2][3] = 2;
        coefficients[2][4] = 1;
        isShiftable = false;
        divisor = 42;
        break;

    case ErrorDiffusionAlrogithm::ATKINSON:
        coefficients[0][3] = 1;
        coefficients[0][4] = 1;
        coefficients[1][1] = 1;
        coefficients[1][2] = 1;
        coefficients[1][3] = 1;
        coefficients[2][2] = 1;
        isShiftable = true;
        divisor = 3;
        break;

    case ErrorDiffusionAlrogithm::BURKES:
        coefficients[0][3] = 8;
        coefficients[0][4] = 4;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 8;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        isShiftable = true;
        divisor = 5;
        break;

    case ErrorDiffusionAlrogithm::SIERRA:
        coefficients[0][3] = 5;
        coefficients[0][4] = 3;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 5;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        coefficients[2][1] = 2;
        coefficients[2][2] = 3;
        coefficients[2][3] = 2;
        isShiftable = true;
        divisor = 5;
        break;

    case ErrorDiffusionAlrogithm::SIERRA_TWO_ROWS:
        coefficients[0][3] = 4;
        coefficients[0][4] = 3;
        coefficients[1][0] = 1;
        coefficients[1][1] = 2;
        coefficients[1][2] = 3;
        coefficients[1][3] = 2;
        coefficients[1][4] = 1;
        isShiftable = true;
        divisor = 4;
        break;

    case ErrorDiffusionAlrogithm::SIERRA_LITE:
        coefficients[0][3] = 2;
        coefficients[1][1] = 1;
        coefficients[1][2] = 1;
        isShiftable = true;
        divisor = 2;
        break;
    
    default:
        throw std::invalid_argument("Invalid algorithm");
    }
}

void ImageEditor::addError(int& pixel, int error, int coefficient, bool isShiftable, int divisor)
{
    if (isShiftable)
    {
        pixel += ((error * coefficient) >> divisor);
    }
    else
    {
        pixel += (error * coefficient/divisor);
    }
}

void ImageEditor::spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height,
                                unsigned int width, int coefficients[3][5], int error, 
                                std::vector<int>& pixels, bool isShiftable, int divisor)
{
    if (currentI >= height || currentJ >= width)
    {
        throw std::invalid_argument("Current pixel is outside the image");
    }

    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 5; ++j)
        {
            // 2 2
            if (coefficients[i][j] > 0 && isInsideTheImage(currentI+i, currentJ+j-2, height, width))
            {
                addError(pixels[(currentI+i)*width + currentJ+j-2], error, coefficients[i][j], isShiftable, divisor);
            }
        }
    }
}

Image* ImageEditor::errorDiffusionDithering(ErrorDiffusionAlrogithm alrorithm)
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
            int oldPixel = this->averagePixels[i*width + j];
            int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = {};
            bool isShiftable = true;
            int divisor = 1;
            getCoefficientTable(alrorithm, coefficients, isShiftable, divisor);
            spreadError(i, j, height, width, coefficients, error, averagePixels, isShiftable, divisor);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}

Image* ImageEditor::orderedDithering(OrderedDitheringAlgorithm algorithm)
{
    int fourXfourMatrix[4][4] = 
    {
        { 0,  8,  2, 10},
        {12,  4, 14,  6},
        { 3, 11,  1,  9},
        {15,  7, 13,  5}
    };

    int eightXEightMatrix[8][8] = 
    {
        { 0, 32,  8, 40,  2, 34, 10, 42},
        {48, 16, 56, 24, 50, 18, 58, 26}, 
        {12, 44,  4, 36, 14, 46,  6, 38}, 
        {60, 28, 52, 20, 62, 30, 54, 22}, 
        { 3, 35, 11, 43,  1, 33,  9, 41}, 
        {51, 19, 59, 27, 49, 17, 57, 25},
        {15, 47,  7, 39, 13, 45,  5, 37},
        {63, 31, 55, 23, 61, 29, 53, 21} 
    };

    std::vector<RGB> newPixels;
    ImageType type = this->toBeEdited->getType();
    unsigned int width = this->toBeEdited->getWidth();
    unsigned int height = this->toBeEdited->getHeight();
    unsigned int maxValue = this->toBeEdited->getMaxValue();

    for (std::size_t i = 0; i < height; ++i)
    {
        int row = (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX) ? (i % 4) : (i % 8);
        for (std::size_t j = 0; j < width; ++j)
        {
            int column = (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX) ? (j % 4) : (j % 8);
            int oldPixel = this->averagePixels[i*width + j];
            int newPixel;
            
            if (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX)
            {
                if ((oldPixel >> 4) < fourXfourMatrix[row][column])
                {
                    newPixel = 0;
                }
                else
                {
                    newPixel = maxValue;
                }
            }
            else
            {
                if ((oldPixel >> 2) < eightXEightMatrix[row][column])
                {
                    newPixel = 0;
                }
                else
                {
                    newPixel = maxValue;
                }
            }

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}