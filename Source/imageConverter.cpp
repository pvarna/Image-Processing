#include "../Headers/imageConverter.h"
#include "../Headers/floydSteinberg.h"

ImageConverter::ImageConverter(Image* image)
{
    this->image = image;
}

Image* ImageConverter::bitMaptoGrayMap()
{
    this->image->setType(ImageType::GRAYMAP);

    return new Image(*this->image);
}

Image* ImageConverter::bitMaptoPixMap()
{
    this->image->setType(ImageType::PIXMAP);

    return new Image(*this->image);
}

Image* ImageConverter::grayMaptoBitMap()
{
    FloydSteinberg alg(this->image);

    Image* newImage = alg.dither();
    newImage->setType(ImageType::BITMAP);

    return newImage;
}

Image* ImageConverter::grayMaptoPixMap()
{
    this->image->setType(ImageType::PIXMAP);

    return new Image(*this->image);
}

Image* ImageConverter::pixMaptoBitMap()
{
    FloydSteinberg alg(this->image);

    Image* newImage = alg.dither();
    newImage->setType(ImageType::BITMAP);

    return newImage;
}

int ImageConverter::RGBToGrayscale(RGB color)
{
    int max = std::max(color.red, std::max(color.green, color.blue));
    int min = std::min(color.red, std::min(color.green, color.blue));

    return static_cast<int>((static_cast<double>(min) + static_cast<double>(max)) / 2);
}

Image* ImageConverter::pixMaptoGrayMap()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    for (std::size_t i = 0; i < width * height; ++i)
    {
        int grayScale = this->RGBToGrayscale((*this->image)[i]);
        (*this->image)[i].red = grayScale;
        (*this->image)[i].green = grayScale;
        (*this->image)[i].blue = grayScale;
    }

    this->image->setType(ImageType::GRAYMAP);

    return new Image(*this->image);
}