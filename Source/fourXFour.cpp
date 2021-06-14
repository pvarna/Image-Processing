#include "../Headers/fourXFour.h"

int FourXFour::coefficients[MAX_TABLE_SIDE][MAX_TABLE_SIDE]
{
    { 0,  8,  2, 10,  0,  0,  0,  0},
    {12,  4, 14,  6,  0,  0,  0,  0},
    { 3, 11,  1,  9,  0,  0,  0,  0},
    {15,  7, 13,  5,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0}
};

FourXFour::FourXFour(Image* image) : OrderedDitheringAlgorithm(image, FourXFour::coefficients, 4, 4)
{}