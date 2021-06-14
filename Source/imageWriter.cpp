#include "../Headers/imageWriter.h"
#include "../Headers/imageReader.h"
#include <cstring>
#include <fstream>
#include <iostream>

ImageWriter::ImageWriter(std::string path, Image* image) : ImageOpener(path, std::ios::out | std::ios::trunc)
{
    if (!image)
    {
        throw std::invalid_argument("No image is loaded");
    }

    this->image = image;
}
