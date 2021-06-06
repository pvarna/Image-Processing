#pragma once

#include "image.h"
#include "enums.h"
#include <string>
class ImageWriter
{
private:
    Image* image;
    std::string path;
    ImageType type;

    bool fileExists(std::string path);

    void saveMetaData(std::ofstream& file);

    void saveBitMap(std::ofstream& file);
    void saveGrayMap(std::ofstream& file);
    void savePixMap(std::ofstream& file);

public:
    ImageWriter(std::string path, Image* image);

    void saveImage();
};