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
    this->path = path;
    this->type = image->getType();
}

void ImageWriter::saveMetaData()
{
    switch (this->type)
    {
    case ImageType::BITMAP:
        this->file << "P1" << std::endl;
        break;

    case ImageType::GRAYMAP:
        this->file << "P2" << std::endl;
        break;

    case ImageType::PIXMAP:
        this->file << "P3" << std::endl;
        break;
    }

    file << this->image->getWidth() << " " << this->image->getHeight() << std::endl;
}

void ImageWriter::saveBitMap()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    this->saveMetaData();
    
    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            this->file << std::endl;
        }
        
        if ((*this->image)[i].red == RGB_WHITE)
        {
            this->file << "0 "; 
        }
        else
        {
            this->file << "1 ";
        }
    }
}

void ImageWriter::saveGrayMap()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    this->saveMetaData();
    this->file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            this->file << std::endl;
        }
        this->file << (*this->image)[i].red << " ";
    }
}

void ImageWriter::savePixMap()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    this->saveMetaData();
    this->file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        file << (*this->image)[i] << std::endl;
    }
}

void ImageWriter::saveImage()
{
    file.seekp(0, std::ios::beg);

    switch (this->type)
    {
    case ImageType::BITMAP:
        this->saveBitMap();
        break;

    case ImageType::GRAYMAP:
        this->saveGrayMap();
        break;

    case ImageType::PIXMAP:
        this->savePixMap();
        break;
    
    default:
        throw std::invalid_argument("Unknown image type");
        break;
    } 
}