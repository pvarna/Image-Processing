#pragma once
#include "image.h"
#include "imageReader.h"

class ImageProcessor
{
private:
    Image* image;
    ImageReader imageReader;
};