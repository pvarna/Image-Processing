#pragma once

#include "enums.h"
#include <fstream>
#include <string>

class ImageOpener
{
protected:
    std::fstream file;
    std::string path;
    ImageType type;

    ImageOpener(std::string path, std::ios::openmode mode);

public:
    ~ImageOpener();
};