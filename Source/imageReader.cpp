#include "../Headers/imageReader.h"
#include "../Headers/consts.h"
#include <cstddef>
#include <iostream>
#include <fstream>

ImageReader::ImageReader(std::string path)
{
    this->type = this->getTypeOfImage(path);

    this->readData(path);
}

Image* ImageReader::loadImage()
{
    Image* image = nullptr;

    switch (this->type)
    {
    case ImageType::BITMAP:
        image = this->loadBitMap();
        break;

    case ImageType::GRAYMAP:
        image = this->loadGrayMap();
        break;

    case ImageType::PIXMAP:
        image = this->loadPixMap();
        break;

    default:
        throw std::invalid_argument("Invalid image format");
    }

    return image;
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

    if (fileExtension.size() != EXTENSION_LENGTH || 
        (fileExtension != "pbm" && fileExtension != "pgm" && fileExtension != "ppm"))
    {
        return ImageType::UNKNOWN;
    }

    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::invalid_argument("Problem while opening the file");
    }

    std::string firstLine;
    std::getline(file, firstLine);

    file.seekg(0, std::ios::beg);
    file.close();

    std::string magicNumber = "";
    magicNumber.push_back(firstLine[0]);
    magicNumber.push_back(firstLine[1]);

    if ((fileExtension == "pbm" && magicNumber != "P1") ||
        (fileExtension == "pgm" && magicNumber != "P2") ||
        (fileExtension == "ppm" && magicNumber != "P3"))
    {
        throw std::runtime_error("Mismatch between the file extension and the magic number");
    }

    switch (magicNumber[1])
    {
    case '1':
        return ImageType::BITMAP;

    case '2':
        return ImageType::GRAYMAP;

    case '3':
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

    std::string currentLine;
    while (std::getline(file, currentLine))
    {
        this->removeExtraWhitespaces(currentLine);

        std::vector<std::string> dataCurrentLine = this->parseString(currentLine);
        for (std::size_t i = 0; i < dataCurrentLine.size(); ++i)
        {
            if (!isNumber(dataCurrentLine[i]))
            {
                throw std::invalid_argument("Corrupted file");
            }
            this->data.push_back(dataCurrentLine[i]);
        }
    }

    file.close();
}

Image* ImageReader::loadBitMap()
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);

    std::size_t dataSize = this->data.size();

    if ((dataSize - BITMAP_METADATA_COUNT) != (width * height))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<RGB> pixels;
    for (std::size_t i = BITMAP_METADATA_COUNT; i < dataSize; ++i)
    {
        std::size_t currentSize = this->data[i].size();
        for (std::size_t j = 0; j < currentSize; ++j)
        {
            if (this->data[i][j] == '0')
            {
                pixels.push_back(RGB(RGB_WHITE, RGB_WHITE, RGB_WHITE));
            }
            else if (this->data[i][j] == '1')
            {
                pixels.push_back(RGB(RGB_BLACK, RGB_BLACK, RGB_BLACK));
            }
            else
            {
                throw std::invalid_argument("Corrupted file");
            }
        }
    }

   return new Image(ImageType::BITMAP, width, height, DEFAULT_MAX_VALUE, pixels);
}

Image* ImageReader::loadGrayMap()
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

    std::vector<RGB> pixels;

    for (std::size_t i = GRAYMAP_PIXMAP_METADATA_COUNT; i < dataSize; ++i)
    {
        unsigned int currentNumber = std::stoi(this->data[i]);
        
        if (currentNumber > DEFAULT_MAX_VALUE)
        {
            throw std::invalid_argument("Corrupted file");
        }
        else if (currentNumber > maxValue)
        {
            pixels.push_back(RGB(maxValue, maxValue, maxValue));
        }
        else
        {
            pixels.push_back(RGB(currentNumber, currentNumber, currentNumber));
        }
    }

    return new Image(ImageType::GRAYMAP, width, height, maxValue, pixels);
}

Image* ImageReader::loadPixMap()
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

        pixels.push_back(RGB(currentRed, currentGreen, currentBlue));
    }

    return new Image(ImageType::PIXMAP, width, height, maxValue, pixels);
}