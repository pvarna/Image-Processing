#include "../Headers/floydSteinbergFalse.h"

int FloydSteinbergFalse::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 3, 0},
    {0, 0, 3, 2, 0},
    {0, 0, 0, 0, 0}
};

FloydSteinbergFalse::FloydSteinbergFalse(Image* image) : ErrorDiffusionAlgorithm(image, FloydSteinbergFalse::coefficientTable, true, 3)
{}