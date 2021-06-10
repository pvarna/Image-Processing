#include "imageOpener.h"

ImageOpener::ImageOpener(std::string path, std::ios::openmode mode) : file(path.c_str(), mode)
{
    if(!file.is_open()) 
    {
        throw std::runtime_error("could not open file " + std::string(path));
    }

    this->path = path;
    this->type = ImageType::UNKNOWN;
}

ImageOpener::~ImageOpener()
{
    this->file.close();
}