#pragma once

#include "image.h"

class ImageEditor
{
private:
    Image* toBeEdited;

    bool isCloserToZero(int value, int maxValue);

public:
    ImageEditor(Image* image);

    Image* oneDimensionalErrorDiffusion();
    Image* twoDimensionalErrorDiffusion();
};