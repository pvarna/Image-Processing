#include "../Headers/bitMap.h"
#include <stdexcept>
#include <iostream>
#include <fstream>

BitMap::BitMap(unsigned int width, unsigned int height, std::vector<bool> pixels)
    : Image("P1", width, height)
{
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

void BitMap::print()
{
    Image::print();
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

/*void BitMap::write(std::string path)
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
            std::cout << "tuka???" << std::endl;
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
    
    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            file << std::endl;
        }
        file << this->pixels[i] << " ";
    }

    file.close();
}*/

bool BitMap::operator [] (std::size_t index) const
{
    if (index >= this->pixels.size())
    {
        throw std::overflow_error("Invalid index");
    }

    return this->pixels[index];
}