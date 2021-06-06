#pragma once
#include "image.h"

class ImageProcessor
{
private:
    Image* imageToOpen;
    Image* imageToSave;    
public:
    ImageProcessor();
    ImageProcessor(const ImageProcessor& other) = delete;
    ImageProcessor& operator = (const ImageProcessor& other) = delete;
    ~ImageProcessor();

    void readImage(std::string path);
    void saveImage(std::string path);

    void printImage();

    void doDithering();
};