#include "../Headers/imageReader.h"

#include <cstddef>
#include <iostream>
#include <fstream>

ImageReader::ImageReader(std::string path) : ImageOpener(path, std::ios::in) 
{
    this->readData();
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

void ImageReader::readData()
{
    this->file.seekg(MAGIC_NUMBER_LENGTH, std::ios::beg);

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
}