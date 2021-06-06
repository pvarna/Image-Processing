#include "../Headers/imageProcessor.h"
#include "../Headers/imageReader.h"
#include "../Headers/imageWriter.h"
#include "../Headers/imageEditor.h"
#include <iostream>

ImageProcessor::ImageProcessor()
{
    this->imageToOpen = nullptr;
    this->imageToSave = nullptr;
}

void ImageProcessor::readImage(std::string path)
{
    ImageReader reader(path);

    if (this->imageToOpen)
    {
        delete this->imageToOpen;
    }
    this->imageToOpen = reader.loadImage();
}

void ImageProcessor::saveImage(std::string path)
{
    if (!this->imageToSave)
    {
        throw std::invalid_argument("No image is loaded");
    }

    ImageWriter writer(path, this->imageToSave);

    writer.saveImage();
}

void ImageProcessor::doDithering()
{
    ImageEditor editor(this->imageToOpen);

    if (this->imageToSave)
    {
        std::invalid_argument("New image already loaded");
    }

    this->imageToSave = editor.twoDimensionalErrorDiffusion();
}

/*void ImageProcessor::printImage()
{
    if (!this->image)
    {
        std::cout << "No image loaded" << std::endl;
        return;
    }

    this->image->print();
}*/

ImageProcessor::~ImageProcessor()
{
    if (this->imageToOpen)
    {
        delete this->imageToOpen;
    }

    if (this->imageToSave)
    {
        delete this->imageToSave;
    }
}