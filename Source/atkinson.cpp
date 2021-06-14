#include "../Headers/atkinson.h"
#include <iostream>

int Atkinson::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 1, 1},
    {0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0}
};

Atkinson::Atkinson(Image* image) : ErrorDiffusionAlgorithm(image, Atkinson::coefficientTable, true, 3)
{}