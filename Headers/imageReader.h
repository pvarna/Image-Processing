#pragma once

#include "image.h"
#include <string>
#include <vector>

enum class ImageType
{
    UNKNOWN = -1,
    BITMAP,
    GRAYMAP,
    PIXMAP
};

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

    void loadBitMap(Image* image);
    void loadGrayMap(Image* image);
    void loadPixMap(Image* image);

public:
    ImageReader(std::string path, Image* image);
};