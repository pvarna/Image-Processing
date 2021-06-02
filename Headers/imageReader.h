#pragma once

#include "image.h"
#include "enums.h"
#include <string>
#include <vector>

class ImageReader
{
private:
    ImageType type;
    std::vector<std::string> data;

    ImageType getTypeOfImage(std::string path);

    bool isDigit(char ch);
    bool isNumber(std::string string);

    void removeExtraWhitespaces(std::string& string);
    std::vector<std::string> parseString(std::string string);

    void readData(std::string path);

    Image* loadBitMap();
    Image* loadGrayMap();
    Image* loadPixMap();

public:
    ImageReader(std::string path);

    Image* loadImage();
};