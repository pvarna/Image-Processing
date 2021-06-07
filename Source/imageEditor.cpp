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
            int oldPixel = this->averagePixels[i*width + j];
            //std::cout << oldPixel << std::endl;
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

            int coefficients[3][5] = 
            {
                {0, 0, 0, 1, 0},
                {0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, false, 1);

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

    for (std::size_t i = 0; i < height; ++i)
    {
        int error = 0;
        for (std::size_t j = 0; j < width; ++j)
        {
            int oldPixel = this->averagePixels[i*width + j];
            std::cout << oldPixel << std::endl;
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

            int coefficients[3][5] = 
            {
                {0, 0, 0, 1, 0},
                {0, 0, 1, 0, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 1);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::floydSteinbergDithering()
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

            int coefficients[3][5] = 
            {
                {0, 0, 0, 7, 0},
                {0, 3, 5, 1, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 4);


            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}

Image* ImageEditor::floydSteinbergFalseDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 3, 0},
                {0, 0, 3, 2, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 3);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}

Image* ImageEditor::jarvisJudiceNinkeDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 7, 5},
                {3, 5, 7, 5, 3},
                {1, 3, 5, 3, 1}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, false, 48);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::stuckiDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 8, 4},
                {2, 4, 8, 4, 2},
                {1, 2, 4, 2, 1}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, false, 42);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::atkinsonDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 1, 1},
                {0, 1, 1, 1, 0},
                {0, 0, 1, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 3);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}

Image* ImageEditor::burkesDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 8, 4},
                {2, 4, 8, 4, 2},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 5);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}

Image* ImageEditor::sierraDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 5, 3},
                {2, 4, 5, 4, 2},
                {0, 2, 3, 2, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 5);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::twoRowSierraDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 4, 3},
                {1, 2, 3, 2, 1},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 4);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::sierraLiteDithering()
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 2, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 2);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);
}

Image* ImageEditor::errorDiffusion(ErrorDiffusionAlrogithm alrorithm)
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
            unsigned int oldPixel = this->averagePixels[i*width + j];
            unsigned int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = 
            {
                {0, 0, 0, 2, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 0, 0, 0}

            };
            this->spreadError(i, j, height, width, coefficients, error, averagePixels, true, 2);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    return new Image(type, width, height, maxValue, newPixels);   
}