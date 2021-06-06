#include "../Headers/bitMap.h"
#include "../Headers/pixMap.h"
#include "../Headers/imageReader.h"
#include "../Headers/imageProcessor.h"
#include <fstream>
#include <iostream>

int main ()
{
    ImageProcessor imageProcessor;

    imageProcessor.readImage("testP1.pbm");
    //imageProcessor.printImage();
    imageProcessor.saveImage("testP1-copy.pbm");

    imageProcessor.readImage("testP2.pgm");
    //.printImage();
    imageProcessor.saveImage("testP2-copy.pgm");

    imageProcessor.readImage("testP3.ppm");
    //imageProcessor.printImage();
    imageProcessor.saveImage("testP3-copy.ppm");
    return 0;
}