#include "../Headers/bitMapReader.h"

BitMapReader::BitMapReader(std::string path) : ImageReader(path)
{}

Image* BitMapReader::loadImage()
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);

    std::size_t dataSize = this->data.size();

    if ((dataSize - BITMAP_METADATA_COUNT) != (width * height))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<RGB> pixels;
    for (std::size_t i = BITMAP_METADATA_COUNT; i < dataSize; ++i)
    {
        std::size_t currentSize = this->data[i].size();
        for (std::size_t j = 0; j < currentSize; ++j)
        {
            if (this->data[i][j] == '0')
            {
                pixels.push_back(RGB(RGB_WHITE, RGB_WHITE, RGB_WHITE));
            }
            else if (this->data[i][j] == '1')
            {
                pixels.push_back(RGB(RGB_BLACK, RGB_BLACK, RGB_BLACK));
            }
            else
            {
                throw std::invalid_argument("Corrupted file");
            }
        }
    }

   return new Image(ImageType::BITMAP, width, height, DEFAULT_MAX_VALUE, pixels);
}