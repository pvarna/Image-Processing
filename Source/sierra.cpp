#include "../Headers/sierra.h"

int Sierra::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 5, 3},
    {2, 4, 5, 4, 2},
    {0, 2, 3, 2, 0}
};

Sierra::Sierra(Image* image) : ErrorDiffusionAlgorithm(image, Sierra::coefficientTable, true, 5)
{}