#include "../Headers/stucki.h"

int Stucki::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 8, 4},
    {2, 4, 8, 4, 2},
    {1, 2, 4, 2, 1}
};

Stucki::Stucki(Image* image) : ErrorDiffusionAlgorithm(image, Stucki::coefficientTable, false, 42)
{}