#include "../Headers/bitMap.h"
#include "../Headers/pixMap.h"
#include "../Headers/imageReader.h"
#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main ()
{
    ImageProcessor imageProcessor;

    imageProcessor.readImage("testP3-copy.ppm");
    imageProcessor.printImage();
    imageProcessor.saveImage("testP3-copy-copy.ppm");
    return 0;
}