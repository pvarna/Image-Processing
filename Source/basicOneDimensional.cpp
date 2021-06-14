#include "../Headers/basicOneDimensional.h"

int BasicOneDimensional::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

BasicOneDimensional::BasicOneDimensional(Image* image) : ErrorDiffusionAlgorithm(image, BasicOneDimensional::coefficientTable, false, 1)
{}