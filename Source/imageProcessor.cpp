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

    this->imageToSave = editor.orderedDithering(OrderedDitheringAlgorithm::EIGHT_X_EIGHT_BAYER_MATRIX);
}

void ImageProcessor::crop()
{
    ImageEditor editor(this->imageToOpen);

    if (this->imageToSave)
    {
        std::invalid_argument("New image already loaded");
    }

    this->imageToSave = editor.cropImage(100, 100, 300, 300);
}

void ImageProcessor::resize()
{
    ImageEditor editor(this->imageToOpen);

    if (this->imageToSave)
    {
        std::invalid_argument("New image already loaded");
    }

    this->imageToSave = editor.resize(200);
}

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