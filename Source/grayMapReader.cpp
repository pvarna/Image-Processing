#include "../Headers/grayMapReader.h"

GrayMapReader::GrayMapReader(std::string path) : ImageReader(path)
{}

Image* GrayMapReader::loadImage()
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);
    unsigned int maxValue = std::stoi(this->data[2]);

    if (maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::size_t dataSize = this->data.size();

    if ((dataSize - GRAYMAP_PIXMAP_METADATA_COUNT) != (width * height))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<RGB> pixels;

    for (std::size_t i = GRAYMAP_PIXMAP_METADATA_COUNT; i < dataSize; ++i)
    {
        int currentNumber = std::stoi(this->data[i]);
        
        if (currentNumber > DEFAULT_MAX_VALUE)
        {
            throw std::invalid_argument("Corrupted file");
        }
        else if (currentNumber > maxValue)
        {
            pixels.push_back(RGB(maxValue, maxValue, maxValue));
        }
        else
        {
            pixels.push_back(RGB(currentNumber, currentNumber, currentNumber));
        }
    }

    return new Image(ImageType::GRAYMAP, width, height, maxValue, pixels);
}