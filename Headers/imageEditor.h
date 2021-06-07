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

    void getCoefficientTable(ErrorDiffusionAlrogithm alrorithm, int coefficients[3][5], bool& isShiftable, int& divisor);

    void addError(int& pixel, int error, int coefficient, bool isShiftable, int divisor);

    void spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height, unsigned int width, int coefficients[3][5], int error, std::vector<int>& pixels, bool isShiftable, int divisor);

public:
    ImageEditor(Image* image);

    Image* oneDimensionalErrorDiffusion();
    Image* twoDimensionalErrorDiffusion();
    Image* floydSteinbergDithering();
    Image* floydSteinbergFalseDithering();
    Image* jarvisJudiceNinkeDithering(); // problem
    Image* stuckiDithering(); // problem
    Image* atkinsonDithering();
    Image* burkesDithering();
    Image* sierraDithering();
    Image* twoRowSierraDithering();
    Image* sierraLiteDithering();

    Image* errorDiffusion(ErrorDiffusionAlrogithm alrorithm);
};