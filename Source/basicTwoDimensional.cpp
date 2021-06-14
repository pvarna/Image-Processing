#include "../Headers/basicTwoDimensional.h"

int BasicTwoDimensional::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

BasicTwoDimensional::BasicTwoDimensional(Image* image) : ErrorDiffusionAlgorithm(image, BasicTwoDimensional::coefficientTable, true, 1)
{}