#include "../Headers/imageWriter.h"
#include "../Headers/bitMap.h"
#include "../Headers/grayMap.h"
#include "../Headers/pixMap.h"
#include <cstring>
#include <fstream>
#include <iostream>

ImageWriter::ImageWriter(std::string path, Image* image)
{
    if (!image)
    {
        throw std::invalid_argument("No image is loaded");
    }

    this->image = image;
    this->path = path;
    this->type = this->getTypeOfImage(image);
}

ImageType ImageWriter::getTypeOfImage(Image* image)
{
    if (!image)
    {
        return ImageType::UNKNOWN;
    }

    const char* magicNumber = image->getMagicNumber();

    if (strcmp(magicNumber, "P1") == 0)
    {
        return ImageType::BITMAP;
    }
    else if (strcmp(magicNumber, "P2") == 0)
    {
        return ImageType::GRAYMAP;
    }
    else if (strcmp(magicNumber, "P3") == 0)
    {
        return ImageType::PIXMAP;
    }

    return ImageType::UNKNOWN;
}

bool ImageWriter::fileExists(std::string path)
{
    std::ifstream file(path.c_str());

    bool result = file.good();
    file.close();

    return result;
}

void ImageWriter::saveBitMap(std::ofstream& file)
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();

    file << this->image->getMagicNumber() << std::endl;
    file << width << " " << height << std::endl;
    
    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            file << std::endl;
        }
        file << (*dynamic_cast<BitMap*>(this->image))[i] << " ";
    }
}

void ImageWriter::saveGrayMap(std::ofstream& file)
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = dynamic_cast<GrayMap*>(this->image)->getMaxValue();
    
    file << this->image->getMagicNumber() << std::endl;
    file << width << " " << height << std::endl;
    file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            file << std::endl;
        }
        file << (*dynamic_cast<GrayMap*>(this->image))[i] << " ";
    }
}

void ImageWriter::savePixMap(std::ofstream& file)
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = dynamic_cast<PixMap*>(this->image)->getMaxValue();

    file << this->image->getMagicNumber() << std::endl;
    file << width << " " << height << std::endl;
    file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        file << (*dynamic_cast<PixMap*>(this->image))[i] << std::endl;
    }
}

void ImageWriter::saveImage()
{
    std::ofstream file;

    if (fileExists(this->path))
    {
        file.open(this->path.c_str(), std::ios::app);

        if (!file.is_open())
        {
            throw std::invalid_argument("Problem while opening the file!");
        }

        std::cout << "This file already exists. Are you sure you want to overwrite the data in the file? [Y/n]: ";
        char choice;
        do
        {
            std::cin >> choice;
            std::cin.ignore();
            if (tolower(choice) != 'y' && tolower(choice) != 'n' && choice != '\n')
            {
                std::cout << "Invalid choice! Try again [Y/n]: ";
            }
        } while (tolower(choice) != 'y' && tolower(choice) != 'n' && choice != '\n');

        if (tolower(choice) == 'n')
        {
            std::cout << "tuka???" << std::endl;
            file.close();
            return;
        }
    }

    file.open(this->path.c_str(), std::ios::trunc);
    file.seekp(0, std::ios::beg);

    if (!file.is_open())
    {
        throw std::invalid_argument("Problem while opening the file!");
    }

    switch (this->type)
    {
    case ImageType::BITMAP:
        this->saveBitMap(file);
        break;

    case ImageType::GRAYMAP:
        this->saveGrayMap(file);
        break;

    case ImageType::PIXMAP:
        this->savePixMap(file);
        break;
    
    default:
        throw std::invalid_argument("Unknown image type");
        break;
    } 

    file.close();
}