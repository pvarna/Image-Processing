#include "../Headers/sierraLite.h"

int SierraLite::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 2, 0},
    {0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0}
};

SierraLite::SierraLite(Image* image) : ErrorDiffusionAlgorithm(image, SierraLite::coefficientTable, true, 2)
{}