#include "../Headers/burkes.h"

int Burkes::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 8, 4},
    {2, 4, 8, 4, 2},
    {0, 0, 0, 0, 0}
};

Burkes::Burkes(Image* image) : ErrorDiffusionAlgorithm(image, Burkes::coefficientTable, true, 5)
{}