#include "../Headers/grayMapWriter.h"

GrayMapWriter::GrayMapWriter(std::string path, Image* image) : ImageWriter(path, image)
{}

void GrayMapWriter::saveImage()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    this->file << "P2" << std::endl;
    this->file << width << " " << height << std::endl;
    this->file << maxValue << std::endl;

    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            this->file << std::endl;
        }
        this->file << (*this->image)[i].red << " ";
    }
}