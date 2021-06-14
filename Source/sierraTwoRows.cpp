#include "../Headers/sierraTwoRows.h"

int SierraTwoRows::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 4, 3},
    {1, 2, 3, 2, 1},
    {0, 0, 0, 0, 0}
};

SierraTwoRows::SierraTwoRows(Image* image) : ErrorDiffusionAlgorithm(image, SierraTwoRows::coefficientTable, true, 4)
{}