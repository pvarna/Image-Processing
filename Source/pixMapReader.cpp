#include "../Headers/pixMapReader.h"

PixMapReader::PixMapReader(std::string path) : ImageReader(path)
{}

Image* PixMapReader::loadImage()
{
    unsigned int width = std::stoi(this->data[0]);
    unsigned int height = std::stoi(this->data[1]);
    unsigned int maxValue = std::stoi(this->data[2]);

    if (maxValue > DEFAULT_MAX_VALUE)
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::size_t dataSize = this->data.size();

    if ((dataSize - GRAYMAP_PIXMAP_METADATA_COUNT) != (width * height * 3))
    {
        throw std::invalid_argument("Corrupted file");
    }

    std::vector<RGB> pixels;

    for (std::size_t i = 3; i < dataSize; i+=3)
    {
        int currentRed = std::stoi(this->data[i]);
        int currentGreen = std::stoi(this->data[i+1]);
        int currentBlue = std::stoi(this->data[i+2]);
        if (currentRed > DEFAULT_MAX_VALUE || currentGreen > DEFAULT_MAX_VALUE || currentBlue > DEFAULT_MAX_VALUE)
        {
            throw std::invalid_argument("Corrupted file");
        }

        if (currentRed > maxValue)
        {
            currentRed = maxValue;
        }

        if (currentGreen > maxValue)
        {
            currentGreen = maxValue;
        }

        if (currentBlue > maxValue)
        {
            currentBlue = maxValue;
        }

        pixels.push_back(RGB(currentRed, currentGreen, currentBlue));
    }

    return new Image(ImageType::PIXMAP, width, height, maxValue, pixels);
}