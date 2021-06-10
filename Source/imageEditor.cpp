#include "../Headers/imageEditor.h"
#include "../Headers/rgb.h"
#include "../Headers/enums.h"
#include "../Headers/imageReader.h"
#include "../Headers/imageWriter.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iostream>

ImageEditor::ImageEditor()
{
    this->image = nullptr;
    this->currentFileName = "";
    this->unsavedChanges = false;
}

ImageEditor::~ImageEditor()
{
    this->deallocate();
}

std::string ImageEditor::getCurrentFileName() const
{
    return this->currentFileName;
}

Image* ImageEditor::getImage() const
{
    return this->image;
}

void ImageEditor::getFileName(std::string path)
{
    std::size_t found = path.find_last_of("/\\");

    if (found == std::string::npos)
    {
        this->currentFileName = path;
        return;
    }

    this->currentFileName = path.substr(found + 1);
}

bool ImageEditor::close()
{
    if (this->unsavedChanges)
    {
        std::cout << "There are unsaved changes to the image. Are you sure you want to close it? [Y/n]: ";
        char choice;
        do
        {
            std::cin >> choice;
            std::cin.ignore();
            if (tolower(choice) != 'y' && tolower(choice) != 'n' && choice != '\n')
            {
                std::cout << "Invalid choice! Try again [Y/n]: ";
            }
        } while (tolower(choice) != 'y' && tolower(choice) != 'n' && choice != '\n');

        if (tolower(choice) == 'n')
        {
            return false;
        }
    }

    this->deallocate();
    this->unsavedChanges = false;
    if (!this->currentFileName.empty())
    {
        std::cout << "Successfully closed " << this->currentFileName << std::endl;
    }
    this->currentFileName.clear();
    this->currentFileName = "";

    return true;
}

void ImageEditor::deallocate()
{
    if (this->image)
    {
        delete this->image;
        this->image = nullptr;
    }
    this->grayscalePixels.clear();
}

void ImageEditor::loadGrayscalePixels()
{
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();

    for (std::size_t i = 0; i < width * height; ++i)
    {
        this->grayscalePixels.push_back(this->RGBToGrayscale((*this->image)[i]));
    }
}

bool ImageEditor::fileExists(std::string path)
{
    std::ifstream file(path.c_str());

    bool result = file.good();
    file.close();

    return result;
}

void ImageEditor::openImage(std::string path)
{
    ImageReader reader(path);

    this->image = reader.loadImage();

    this->loadGrayscalePixels();
    this->getFileName(path);
    std::cout << "Successfully opened " << this->currentFileName << std::endl;
}

void ImageEditor::saveImage(std::string path, bool save)
{
    if (save && path.empty())
    {
        throw std::invalid_argument("No file is currently opened");
    }

    if (!save)
    {
        if (this->fileExists(path))
        {
            std::cout << "This file already exists. Are you sure you want to overwrite the data in the file? [Y/n]: ";
            char choice;
            do
            {
                std::cin >> choice;
                std::cin.ignore();
                if (tolower(choice) != 'y' && tolower(choice) != 'n')
                {
                    std::cout << "Invalid choice! Try again [Y/n]: ";
                }
            } while (tolower(choice) != 'y' && tolower(choice) != 'n');

            if (tolower(choice) == 'n')
            {
                return;
            }
        }
    }

    std::size_t found = path.find_last_of('.');
    if (found == std::string::npos)
    {
        throw std::invalid_argument("There is not a file extension in the path");
    }

    std::string fileExtension = path.substr(path.find_last_of('.') + 1);

    if (fileExtension != "pbm" && fileExtension != "pgm" && fileExtension != "ppm")
    {
        throw std::invalid_argument("Invalid file extension");
    }

    if (this->image->getType() == ImageType::BITMAP && fileExtension != "pbm")
    {
        if (fileExtension == "pgm")
        {
            this->convertBitMaptoGrayMap();
        }
        else if (fileExtension == "ppm")
        {
            this->convertBitMaptoPixMap();
        }
    }
    else if (this->image->getType() == ImageType::GRAYMAP && fileExtension != "pgm")
    {
        if (fileExtension == "pbm")
        {
            this->convertGrayMaptoBitMap();
        }
        else if (fileExtension == "ppm")
        {
            this->convertGrayMaptoPixMap();
        }
    }
    else if (this->image->getType() == ImageType::PIXMAP && fileExtension != "ppm")
    {
        if (fileExtension == "pbm")
        {
            this->convertPixMaptoBitMap();
        }
        else if (fileExtension == "pgm")
        {
            this->convertPixMaptoGrayMap();
        }
    }

    ImageWriter writer(path, this->image);

    writer.saveImage();
    this->unsavedChanges = false;
    this->getFileName(path);

    std::cout << "Successfully saved " << this->currentFileName << std::endl;
}

void ImageEditor::createImage(unsigned int width, unsigned int height, std::string hexColor)
{
    this->image = new Image(width, height, hexColor);
    this->loadGrayscalePixels();
    this->currentFileName = "";
    this->unsavedChanges = true;
    std::cout << "Created new document with size " << width << "x" << height << " and filled with " <<  hexColor << std::endl;
}

int ImageEditor::RGBToGrayscale(RGB color)
{
    int max = std::max(color.red, std::max(color.green, color.blue));
    int min = std::min(color.red, std::min(color.green, color.blue));

    return static_cast<int>((static_cast<double>(min) + static_cast<double>(max)) / 2);
}

inline bool ImageEditor::isCloserToZero(int value, int maxValue)
{
    return value < (maxValue - value);
}

inline bool ImageEditor::isInsideTheImage(std::size_t i, std::size_t j, unsigned int height, unsigned int width)
{
    return i < height && j < width;
}

void ImageEditor::getCoefficientTable(ErrorDiffusionAlrogithm algorithm, int coefficients[3][5], 
                                        bool& isShiftable, int& divisor)
{
    switch (algorithm)
    {
    case ErrorDiffusionAlrogithm::BASIC_ONE_DIMENSIONAL:
        coefficients[0][3] = 1;
        isShiftable = false;
        divisor = 1;
        break;

    case ErrorDiffusionAlrogithm::BASIC_TWO_DIMENSIONAL:
        coefficients[0][3] = 1;
        coefficients[1][2] = 1;
        isShiftable = true;
        divisor = 1;
        break;

    case ErrorDiffusionAlrogithm::FLOYD_STEINBERG:
        coefficients[0][3] = 7;
        coefficients[1][1] = 3;
        coefficients[1][2] = 5;
        coefficients[1][3] = 1;
        isShiftable = true;
        divisor = 4;
        break;

    case ErrorDiffusionAlrogithm::FLOYD_STEINBERG_FALSE:
        coefficients[0][3] = 3;
        coefficients[1][2] = 3;
        coefficients[1][3] = 2;
        isShiftable = true;
        divisor = 3;
        break;

    case ErrorDiffusionAlrogithm::JARVIS_JUDICE_NINKE:
        coefficients[0][3] = 7;
        coefficients[0][4] = 5;
        coefficients[1][0] = 3;
        coefficients[1][1] = 5;
        coefficients[1][2] = 7;
        coefficients[1][3] = 5;
        coefficients[1][4] = 3;
        coefficients[2][0] = 1;
        coefficients[2][1] = 3;
        coefficients[2][2] = 5;
        coefficients[2][3] = 3;
        coefficients[2][4] = 1;
        isShiftable = false;
        divisor = 48;
        break;

    case ErrorDiffusionAlrogithm::STUCKI:
        coefficients[0][3] = 8;
        coefficients[0][4] = 4;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 8;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        coefficients[2][0] = 1;
        coefficients[2][1] = 2;
        coefficients[2][2] = 4;
        coefficients[2][3] = 2;
        coefficients[2][4] = 1;
        isShiftable = false;
        divisor = 42;
        break;

    case ErrorDiffusionAlrogithm::ATKINSON:
        coefficients[0][3] = 1;
        coefficients[0][4] = 1;
        coefficients[1][1] = 1;
        coefficients[1][2] = 1;
        coefficients[1][3] = 1;
        coefficients[2][2] = 1;
        isShiftable = true;
        divisor = 3;
        break;

    case ErrorDiffusionAlrogithm::BURKES:
        coefficients[0][3] = 8;
        coefficients[0][4] = 4;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 8;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        isShiftable = true;
        divisor = 5;
        break;

    case ErrorDiffusionAlrogithm::SIERRA:
        coefficients[0][3] = 5;
        coefficients[0][4] = 3;
        coefficients[1][0] = 2;
        coefficients[1][1] = 4;
        coefficients[1][2] = 5;
        coefficients[1][3] = 4;
        coefficients[1][4] = 2;
        coefficients[2][1] = 2;
        coefficients[2][2] = 3;
        coefficients[2][3] = 2;
        isShiftable = true;
        divisor = 5;
        break;

    case ErrorDiffusionAlrogithm::SIERRA_TWO_ROWS:
        coefficients[0][3] = 4;
        coefficients[0][4] = 3;
        coefficients[1][0] = 1;
        coefficients[1][1] = 2;
        coefficients[1][2] = 3;
        coefficients[1][3] = 2;
        coefficients[1][4] = 1;
        isShiftable = true;
        divisor = 4;
        break;

    case ErrorDiffusionAlrogithm::SIERRA_LITE:
        coefficients[0][3] = 2;
        coefficients[1][1] = 1;
        coefficients[1][2] = 1;
        isShiftable = true;
        divisor = 2;
        break;
    
    default:
        throw std::invalid_argument("Invalid algorithm");
    }
}

void ImageEditor::addError(int& pixel, int error, int coefficient, bool isShiftable, int divisor)
{
    if (isShiftable)
    {
        pixel += ((error * coefficient) >> divisor);
    }
    else
    {
        pixel += (error * coefficient/divisor);
    }
}

void ImageEditor::spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height,
                                unsigned int width, int coefficients[3][5], int error, 
                                std::vector<int>& pixels, bool isShiftable, int divisor)
{
    if (currentI >= height || currentJ >= width)
    {
        throw std::invalid_argument("Current pixel is outside the image");
    }

    for (std::size_t i = 0; i < 3; ++i)
    {
        for (std::size_t j = 0; j < 5; ++j)
        {
            // 2 2
            if (coefficients[i][j] > 0 && isInsideTheImage(currentI+i, currentJ+j-2, height, width))
            {
                addError(pixels[(currentI+i)*width + currentJ+j-2], error, coefficients[i][j], isShiftable, divisor);
            }
        }
    }
}

void ImageEditor::errorDiffusionDithering(ErrorDiffusionAlrogithm alrorithm)
{
    std::vector<RGB> newPixels;
    ImageType type = this->image->getType();
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    for (std::size_t i = 0; i < height; ++i)
    {
        int error = 0;
        for (std::size_t j = 0; j < width; ++j)
        {
            int oldPixel = this->grayscalePixels[i*width + j];
            int newPixel;

            if (isCloserToZero(oldPixel, maxValue))
            {
                newPixel = 0;
            }
            else
            {
                newPixel = maxValue;
            }
            error = oldPixel - newPixel;

            int coefficients[3][5] = {};
            bool isShiftable = true;
            int divisor = 1;
            getCoefficientTable(alrorithm, coefficients, isShiftable, divisor);
            spreadError(i, j, height, width, coefficients, error, grayscalePixels, isShiftable, divisor);

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    Image* ditheredImage = new Image(type, width, height, maxValue, newPixels);  
    this->deallocate();
    this->image = ditheredImage;
    this->unsavedChanges = true;
    this->loadGrayscalePixels();

    std::cout << "Successfully dithered " << this->currentFileName << std::endl;
}

void ImageEditor::orderedDithering(OrderedDitheringAlgorithm algorithm)
{
    int fourXfourMatrix[4][4] = 
    {
        { 0,  8,  2, 10},
        {12,  4, 14,  6},
        { 3, 11,  1,  9},
        {15,  7, 13,  5}
    };

    int eightXEightMatrix[8][8] = 
    {
        { 0, 32,  8, 40,  2, 34, 10, 42},
        {48, 16, 56, 24, 50, 18, 58, 26}, 
        {12, 44,  4, 36, 14, 46,  6, 38}, 
        {60, 28, 52, 20, 62, 30, 54, 22}, 
        { 3, 35, 11, 43,  1, 33,  9, 41}, 
        {51, 19, 59, 27, 49, 17, 57, 25},
        {15, 47,  7, 39, 13, 45,  5, 37},
        {63, 31, 55, 23, 61, 29, 53, 21} 
    };

    std::vector<RGB> newPixels;
    ImageType type = this->image->getType();
    unsigned int width = this->image->getWidth();
    unsigned int height = this->image->getHeight();
    unsigned int maxValue = this->image->getMaxValue();

    for (std::size_t i = 0; i < height; ++i)
    {
        int row = (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX) ? (i % 4) : (i % 8);
        for (std::size_t j = 0; j < width; ++j)
        {
            int column = (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX) ? (j % 4) : (j % 8);
            int oldPixel = this->grayscalePixels[i*width + j];
            int newPixel;
            
            if (algorithm == OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX)
            {
                if ((oldPixel >> 4) < fourXfourMatrix[row][column])
                {
                    newPixel = 0;
                }
                else
                {
                    newPixel = maxValue;
                }
            }
            else
            {
                if ((oldPixel >> 2) < eightXEightMatrix[row][column])
                {
                    newPixel = 0;
                }
                else
                {
                    newPixel = maxValue;
                }
            }

            newPixels.push_back(RGB(newPixel, newPixel, newPixel));
        }
    }

    Image* ditheredImage = new Image(type, width, height, maxValue, newPixels);  
    this->deallocate();
    this->image = ditheredImage;
    this->unsavedChanges = true;
    this->loadGrayscalePixels();  

    std::cout << "Successfully dithered " << this->currentFileName << std::endl; 
}

void ImageEditor::crop(int x1, int y1, int x2, int y2)
{
    int width = this->image->getWidth();
    int height = this->image->getHeight();

    if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
    {
        throw std::invalid_argument("Indexes must be bigger than or equal to 0");
    }

    if (x1 >= width)
    {
        x1 = width - 1;
    }
    if (x2 >= width)
    {
        x2 = width - 1;
    }
    if (y1 >= height)
    {
        y1 = height - 1;
    }
    if (y2 >= height)
    {
        y2 = height - 1;
    }

    if (x1 == x2 || y1 == y2)
    {
        throw std::invalid_argument("Indexes do not form a rectangle");
    }

    int minX = std::min(x1, x2);
    int maxX = std::max(x1, x2);
    int minY = std::min(y1, y2);
    int maxY = std::max(y1, y2);

    std::vector<RGB> croppedPixels;
    for (std::size_t i = minY; i <= maxY; ++i)
    {
        for (std::size_t j = minX; j <= maxX; ++j)
        {
            croppedPixels.push_back((*this->image)[i*width + j]);
        }
    }

    Image* croppedImage = new Image(this->image->getType(), maxX - minX + 1, maxY - minY + 1, this->image->getMaxValue(), croppedPixels);
    this->deallocate();
    this->image = croppedImage;
    this->unsavedChanges = true;
    this->loadGrayscalePixels(); 

    std::cout << "Successfully cropped " << this->currentFileName << std::endl;
}

void ImageEditor::resize(unsigned int newWidth, unsigned int newHeight)
{
    if (newWidth <= 0 || newHeight <= 0)
    {
        throw std::invalid_argument("New width and new height must be bigger than 0");
    }
    int width = this->image->getWidth();
    int height = this->image->getHeight();
    std::vector<RGB> resizedPixels;

    for (std::size_t i = 0; i < newHeight; ++i)
    {
        for (std::size_t j = 0; j < newWidth; ++j)
        {
            int newI = static_cast<int>(round(static_cast<double>(i)/static_cast<double>(newHeight)*static_cast<double>(height)));
            int newJ = static_cast<int>(round(static_cast<double>(j)/static_cast<double>(newWidth)*static_cast<double>(width)));
            newI = std::min(newI, height - 1);
            newJ = std::min(newJ, width - 1);

            resizedPixels.push_back((*this->image)[newI*width + newJ]);
        }
    }

    Image* resizedImage = new Image(this->image->getType(), newWidth, newHeight, this->image->getMaxValue(), resizedPixels);
    this->deallocate();
    this->image = resizedImage;
    this->unsavedChanges = true;
    this->loadGrayscalePixels(); 

    std::cout << "Successfully resized " << this->currentFileName << std::endl;
}

void ImageEditor::resize(double percentage)
{
    if (percentage <= 0)
    {
        throw std::invalid_argument("The percentage must be bigger than 0");
    }

    unsigned int newWidth = static_cast<unsigned int>(round(static_cast<double>(this->image->getWidth())*percentage/100));
    unsigned int newHeight = static_cast<unsigned int>(round(static_cast<double>(this->image->getHeight())*percentage/100));

    this->resize(newWidth, newHeight);
}

void ImageEditor::convertBitMaptoGrayMap()
{
    this->image->setType(ImageType::GRAYMAP);
}
void ImageEditor::convertBitMaptoPixMap()
{
    this->image->setType(ImageType::PIXMAP);
}
void ImageEditor::convertGrayMaptoBitMap()
{
    this->errorDiffusionDithering(DEFAULT_ALGORITHM);
    this->image->setType(ImageType::BITMAP);
}
void ImageEditor::convertGrayMaptoPixMap()
{
    this->image->setType(ImageType::PIXMAP);
}
void ImageEditor::convertPixMaptoBitMap()
{
    this->errorDiffusionDithering(DEFAULT_ALGORITHM);
    this->image->setType(ImageType::BITMAP);
}
void ImageEditor::convertPixMaptoGrayMap()
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
}