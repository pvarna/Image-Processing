#include "../Headers/imageReader.h"
#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main ()
{
    ImageProcessor imageProcessor;

    imageProcessor.readImage("blue.ppm");
    imageProcessor.resize();

    imageProcessor.saveImage("blueResize3.ppm");
    return 0;
}