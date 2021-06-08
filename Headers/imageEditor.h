#pragma once

#include "image.h"
#include <vector>

class ImageEditor
{
private:
    Image* toBeEdited;
    std::vector<int> averagePixels;

    bool isCloserToZero(int value, int maxValue);

    bool isInsideTheImage(std::size_t i, std::size_t j, unsigned int height, unsigned int width);

    void getCoefficientTable(ErrorDiffusionAlrogithm algorithm, int coefficients[3][5], bool& isShiftable, int& divisor);

    void addError(int& pixel, int error, int coefficient, bool isShiftable, int divisor);

    void spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height, unsigned int width, int coefficients[3][5], int error, std::vector<int>& pixels, bool isShiftable, int divisor);

public:
    ImageEditor(Image* image);

    Image* errorDiffusionDithering(ErrorDiffusionAlrogithm algorithm);
    Image* orderedDithering(OrderedDitheringAlgorithm algorithm);

    Image* cropImage(int x1, int y1, int x2, int y2);
    Image* resize(unsigned int newWidth, unsigned int newHeight);
    Image* resize(double percentage);
};