#include "../Headers/grayMap.h"
#include "../Headers/consts.h"
#include <stdexcept>
#include <cstddef>
#include <fstream>
#include <iostream>

GrayMap::GrayMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<unsigned int> pixels)
    : Image("P2", width, height)
{
    this->maxValue = maxValue;

    if (this->maxValue > DEFAULT_MAX_VALUE)
    {
        std::cout << "tuk?" << std::endl;
        throw std::invalid_argument("Invalid max value");
    }

    std::size_t pixelsSize = pixels.size();

    if (pixelsSize != width * height)
    {
        throw std::invalid_argument("Invalid number of pixels");
    }

    for (std::size_t i = 0; i < pixelsSize; ++i)
    {
        this->pixels.push_back(pixels[i]);
    }
}

void GrayMap::print()
{
    Image::print();
    std::cout << "Max value: " << this->maxValue << std::endl;

    std::size_t sizePixels = this->pixels.size();

    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            std::cout << std::endl;
        }
        std::cout << this->pixels[i] << " ";
    }
    std::cout << std::endl;
}

/*void GrayMap::write(std::string path)
{
    std::ofstream file;

    if (fileExists(path))
    {
        file.open(path.c_str(), std::ios::app);

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
            file.close();
            return;
        }
    }

    file.open(path.c_str(), std::ios::trunc);
    file.seekp(0, std::ios::beg);

    if (!file.is_open())
    {
        throw std::invalid_argument("Problem while opening the file!");
    }
    
    file << this->magicNumber << std::endl;
    file << this->width << " " << this->height << std::endl;
    file << this->maxValue << std::endl;
    
    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        file << this->pixels[i] << " ";
        if (i % width == 0 && i > 0)
        {
            file << std::endl;
        }
    }

    file.close();
}*/

unsigned int GrayMap::getMaxValue() const
{
    return this->maxValue;
}

unsigned int GrayMap::operator [] (std::size_t index) const
{
    if (index >= this->pixels.size())
    {
        throw std::overflow_error("Invalid index");
    }

    return this->pixels[index];
}