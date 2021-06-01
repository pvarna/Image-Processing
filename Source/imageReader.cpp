#include "../Headers/imageReader.h"
#include "../Headers/bitMap.h"
#include "../Headers/grayMap.h"
#include "../Headers/pixMap.h"
#include <cstddef>
#include <iostream>
#include <fstream>

const std::size_t EXTENSION_LENGTH = 3;
const std::size_t MAGIC_NUMBER_LENGTH = 2;
const std::size_t BITMAP_METADATA_COUNT = 2;
const std::size_t GRAYMAP_PIXMAP_METADATA_COUNT = 3;
const std::size_t DEFAULT_MAX_VALUE = 255;

ImageReader::ImageReader(std::string path, Image* image)
{
    this->type = this->getTypeOfImage(path);

    switch (this->type)
    {
    case ImageType::BITMAP:
        this->loadBitMap(image);
        break;

    case ImageType::GRAYMAP:
        this->loadGrayMap(image);
        break;

    case ImageType::PIXMAP:
        this->loadPixMap(image);
        break;

    default:
        throw std::invalid_argument("Invalid image format");
    }
}

bool ImageReader::isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool ImageReader::isNumber(std::string string)
{
    std::size_t stringSize = string.size();

    for (std::size_t i = 0; i < stringSize; ++i)
    {
        if (!isDigit(string[i]))
        {
            return false;
        }
    }

    return true;
}

void ImageReader::removeExtraWhitespaces(std::string& string)
{
    std::size_t currentIndex = 0;
    std::size_t length = string.length();

    std::string result = "";

    while (string[currentIndex] == ' ')
    {
        ++currentIndex;
    }

    bool spaceFound = false;

    while (currentIndex < length)
    {
        if (string[currentIndex] != ' ')
        {
            result.push_back(string[currentIndex++]);
            spaceFound = false;
        }
        else
        {
            if (!spaceFound)
            {
                result.push_back(string[currentIndex++]);
                spaceFound = true;
            }
            else
            {
                ++currentIndex;
            }
        }
    }

    if (result.back() == ' ')
    {
        result.pop_back();
    }

    string = result;
}

std::vector<std::string> ImageReader::parseString(std::string string)
{
    std::vector<std::string> result;
    std::size_t sizeString = string.size();

    std::string currentString;
    for (std::size_t i = 0; i < sizeString; ++i)
    {
        if (string[i] == '#')
        {
            break;
        }
        
        if (string[i] == ' ')
        {
            result.push_back(currentString);
            currentString.clear();
        }
        else if (!isDigit(string[i]))
        {
            throw std::invalid_argument("Corrupted file");
        }
        else
        {
            currentString.push_back(string[i]);
        }
    }

    if (!currentString.empty())
    {
        result.push_back(currentString);
    }

    return result;
}

ImageType ImageReader::getTypeOfImage(std::string path)
{
    std::string fileExtension = path.substr(path.find_last_of('.') + 1);
    //std::cout << fileExtension << std::endl;

    if (fileExtension.size() != EXTENSION_LENGTH || 
        (fileExtension != "pbm" && fileExtension != "pgm" && fileExtension != "ppm"))
    {
        return ImageType::UNKNOWN;
    }

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "tuka stigash li" << std::endl;
        throw std::invalid_argument("Problem while opening the file");
    }

    std::string firstLine;
    std::getline(file, firstLine);

    file.seekg(0, std::ios::beg);
    file.close();

    std::cout << firstLine << std::endl;

    std::string magicNumber = "";
    magicNumber.push_back(firstLine[0]);
    magicNumber.push_back(firstLine[1]);

    std::cout << magicNumber << std::endl;

    if ((fileExtension == "pbm" && magicNumber != "P1") ||
        (fileExtension == "pgm" && magicNumber != "P2") ||
        (fileExtension == "ppm" && magicNumber != "P3"))
    {
        throw std::runtime_error("Discrepancy between the file extension and the magic number");
    }

    switch (magicNumber[1])
    {
    case '1':
        std::cout << "bitmap" << std::endl;
        return ImageType::BITMAP;

    case '2':
    std::cout << "graymap" << std::endl;
        return ImageType::GRAYMAP;

    case '3':
    std::cout << "pixmap" << std::endl;
        return ImageType::PIXMAP;
    }

    return ImageType::UNKNOWN;
}

void ImageReader::readData(std::string path)
{
    std::ifstream file(path.c_str());
    file.seekg(MAGIC_NUMBER_LENGTH, std::ios::beg);

    if (!file.is_open())
    {
        throw std::invalid_argument("Problem while opening the file");
    }

    bool metaDataRead = false;

    std::string currentLine;
    while (std::getline(file, currentLine))
    {
        this->removeExtraWhitespaces(currentLine);
        std::vector<std::string> currentData = this->parseString(currentLine);
        for (std::size_t i = 0; i < currentData.size(); ++i)
        {
            if (!isNumber(currentData[i]))
            {
                throw std::invalid_argument("Corrupted file");
            }
            std::cout << currentData[i] << std::endl;
            this->data.push_back(currentData[i]);
        }
    }

    file.close();
}

void ImageReader::loadBitMap(Image* image)
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);

    std::size_t dataSize = this->data.size();

    if ((dataSize - BITMAP_METADATA_COUNT) != (width * height))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<bool> pixels;
    for (std::size_t i = 2; i < dataSize; ++i)
    {
        std::size_t currentSize = this->data[i].size();
        for (std::size_t j = 0; j < currentSize; ++i)
        {
            pixels.push_back(this->data[i][j] == '1');
        }
    }

    if (image)
    {
        delete image;
    }
    image = new BitMap(width, height, pixels);
}

void ImageReader::loadGrayMap(Image* image)
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);
    unsigned int maxValue = std::stoi(this->data[2]);

    if (maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::size_t dataSize = this->data.size();

    if ((dataSize - GRAYMAP_PIXMAP_METADATA_COUNT) != (width * height))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<unsigned int> pixels;

    for (std::size_t i = 3; i < dataSize; ++i)
    {
        unsigned int currentNumber = std::stoi(this->data[i]);
        if (currentNumber > DEFAULT_MAX_VALUE)
        {
            throw std::invalid_argument("Corrupted file");
        }
        else if (currentNumber > maxValue)
        {
            pixels.push_back(maxValue);
        }
        else
        {
            pixels.push_back(currentNumber);
        }
    }

    if (image)
    {
        delete image;
    }
    image = new GrayMap(width, height, maxValue, pixels);
}

void ImageReader::loadPixMap(Image* image)
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);
    unsigned int maxValue = std::stoi(this->data[2]);

    if (maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::size_t dataSize = this->data.size();

    if ((dataSize - GRAYMAP_PIXMAP_METADATA_COUNT) != (width * height * 3))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<RGB> pixels;

    for (std::size_t i = 3; i < dataSize; i+=3)
    {
        unsigned int currentRed = std::stoi(this->data[i]);
        unsigned int currentGreen = std::stoi(this->data[i+1]);
        unsigned int currentBlue = std::stoi(this->data[i+2]);
        if (currentRed > DEFAULT_MAX_VALUE || currentGreen > DEFAULT_MAX_VALUE || currentBlue > DEFAULT_MAX_VALUE)
        {
            throw std::invalid_argument("Corrupted file");
        }

        if (currentRed > maxValue)
        {
            currentRed = maxValue;
        }

        if (currentGreen > maxValue)
        {
            currentGreen = maxValue;
        }

        if (currentBlue > maxValue)
        {
            currentBlue = maxValue;
        }

        RGB currentPixel(currentRed, currentGreen, currentBlue);
        pixels.push_back(currentPixel);
    }

    if (image)
    {
        delete image;
    }
    image = new PixMap(width, height, maxValue, pixels);   
}