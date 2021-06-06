#include "../Headers/imageProcessor.h"
#include "../Headers/imageReader.h"
#include "../Headers/imageWriter.h"
#include <iostream>

ImageProcessor::ImageProcessor()
{
    this->image = nullptr;
}

void ImageProcessor::readImage(std::string path)
{
    ImageReader reader(path);

    if (this->image)
    {
        delete this->image;
    }
    this->image = reader.loadImage();
}

void ImageProcessor::saveImage(std::string path)
{
    if (!this->image)
    {
        throw std::invalid_argument("No image is loaded");
    }

    ImageWriter writer(path, this->image);

    writer.saveImage();
}

void ImageProcessor::printImage()
{
    if (!this->image)
    {
        std::cout << "No image loaded" << std::endl;
        return;
    }

    this->image->print();
}

ImageProcessor::~ImageProcessor()
{
    if (this->image)
    {
        delete this->image;
    }
}