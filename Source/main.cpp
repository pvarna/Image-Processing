#include "../Headers/imageReader.h"
#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main ()
{
    ImageProcessor imageProcessor;

    imageProcessor.readImage("cube.ppm");
    imageProcessor.doDithering();

    imageProcessor.saveImage("cubeDither2.ppm");
    return 0;
}