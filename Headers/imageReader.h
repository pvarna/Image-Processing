#pragma once

#include "image.h"
#include "enums.h"
#include "imageOpener.h"
#include <string>
#include <vector>

class ImageReader : public ImageOpener
{
private:
    std::vector<std::string> data;

    ImageType getTypeOfImage();

    bool isDigit(char ch);
    bool isNumber(std::string string);

    void removeExtraWhitespaces(std::string& string);
    std::vector<std::string> parseString(std::string string);

    void readData();

    Image* loadBitMap();
    Image* loadGrayMap();
    Image* loadPixMap();

public:
    ImageReader(std::string path);

    Image* loadImage();
};