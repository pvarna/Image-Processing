#include "../Headers/floydSteinberg.h"

int FloydSteinberg::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 7, 0},
    {0, 3, 5, 1, 0},
    {0, 0, 0, 0, 0}
};

FloydSteinberg::FloydSteinberg(Image* image) : ErrorDiffusionAlgorithm(image, FloydSteinberg::coefficientTable, true, 4)
{}