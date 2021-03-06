#include "../Headers/imageOpener.h"

ImageOpener::ImageOpener(std::string path, std::ios::openmode mode) : file(path, mode)
{
    if(!file.is_open()) 
    {
        throw std::runtime_error("could not open file " + std::string(path));
    }
}

ImageOpener::~ImageOpener()
{
    this->file.close();
}