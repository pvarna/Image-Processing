#include "../Headers/jarvisJudiceNinke.h"

int JarvisJudiceNinke::coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH] = 
{
    {0, 0, 0, 7, 5},
    {3, 5, 7, 5, 3},
    {1, 3, 5, 3, 1}
};

JarvisJudiceNinke::JarvisJudiceNinke(Image* image) : ErrorDiffusionAlgorithm(image, JarvisJudiceNinke::coefficientTable, false, 48)
{}