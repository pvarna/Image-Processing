#include "../Headers/pixMapWriter.h"

PixMapWriter::PixMapWriter(std::string path, Image* image) : ImageWriter(path, image)
{}

void PixMapWriter::saveImage()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    this->file << "P3" << std::endl;
    this->file << width << " " << height << std::endl;
    this->file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        file << (*this->image)[i] << std::endl;
    }
}