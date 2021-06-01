#include "../Headers/pixMap.h"
#include <stdexcept>
#include <cstddef>
#include <fstream>
#include <iostream>

PixMap::PixMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels)
    : Image("P3", width, height)
{
    if (this->maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Invalid max value");
    }

    this->maxValue = maxValue;

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

PixMap::PixMap(unsigned int width, unsigned int height, std::string hexCode)
    : Image("P3", width, height)
{
    this->maxValue = DEFAULT_MAX_VALUE;

    std::size_t pixelsSize = width * height;

    for (std::size_t i = 0; i < pixelsSize; ++i)
    {
        this->pixels.push_back(RGB(hexCode));
    }
}

/*inline bool PixMap::fileExists(std::string path)
{
    std::ifstream file(path.c_str());

    bool result = file.good();
    file.close();

    return result;
}*/

/*void PixMap::write(std::string path)
{
    std::ofstream file;

    if (fileExists(path))
    {
        file.open(path.c_str());

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

    file.open(path.c_str());

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
        file << this->pixels[i].red << " " << this->pixels[i].green << " " << this->pixels[i].blue << std::endl;
    }

    file.close();
}

void PixMap::read(std::string path)
{
    std::cout << "Hi" << std::endl;
}*/