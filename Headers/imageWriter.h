#pragma once

#include "image.h"
#include "enums.h"
#include "imageOpener.h"
#include <string>
class ImageWriter : public ImageOpener
{
private:
    Image* image;

    void saveMetaData();

    void saveBitMap();
    void saveGrayMap();
    void savePixMap();

public:
    ImageWriter(std::string path, Image* image);

    void saveImage();
};