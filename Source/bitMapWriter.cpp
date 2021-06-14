#include "../Headers/bitMapWriter.h"

BitMapWriter::BitMapWriter(std::string path, Image* image) : ImageWriter(path, image)
{}

void BitMapWriter::saveImage()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    
    this->file << "P1" << std::endl;
    this->file << width << " " << height << std::endl;
    
    std::size_t sizePixels = width * height;
    for (std::size_t i = 0; i < sizePixels; ++i)
    {
        if (i % width == 0 && i > 0)
        {
            this->file << std::endl;
        }
        
        if ((*this->image)[i].red == RGB_WHITE)
        {
            this->file << "0 "; 
        }
        else
        {
            this->file << "1 ";
        }
    }
}