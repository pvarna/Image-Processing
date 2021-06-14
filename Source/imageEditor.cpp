#include "../Headers/imageEditor.h"
#include "../Headers/rgb.h"
#include "../Headers/enums.h"
#include "../Headers/imageReader.h"
#include "../Headers/bitMapReader.h"
#include "../Headers/grayMapReader.h"
#include "../Headers/pixMapReader.h"
#include "../Headers/imageWriter.h"
#include "../Headers/bitMapWriter.h"
#include "../Headers/grayMapWriter.h"
#include "../Headers/pixMapWriter.h"
#include "../Headers/errorDiffusionAlgorithm.h"
#include "../Headers/orderedDitheringAlgorithm.h"
#include "../Headers/fourXFour.h"
#include "../Headers/eightXEight.h"
#include "../Headers/errorDiffusionAlgorithm.h"
#include "../Headers/basicOneDimensional.h"
#include "../Headers/basicTwoDimensional.h"
#include "../Headers/floydSteinberg.h"
#include "../Headers/floydSteinbergFalse.h"
#include "../Headers/jarvisJudiceNinke.h"
#include "../Headers/stucki.h"
#include "../Headers/atkinson.h"
#include "../Headers/burkes.h"
#include "../Headers/sierra.h"
#include "../Headers/sierraTwoRows.h"
#include "../Headers/sierraLite.h"
#include "../Headers/imageConverter.h"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>

ImageEditor::ImageEditor()
{
    this->image = nullptr;
    this->currentFileName = "";
    this->unsavedChanges = false;
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

ImageEditor::~ImageEditor()
{
    this->deallocate();
}

ImageType ImageEditor::getTypeOfImage(std::string path)
{
    std::ifstream file(path.c_str());

    if (!file.is_open())
    {
        throw std::runtime_error("could not open file " + std::string(path));
    }

    std::string fileExtension = path.substr(path.find_last_of('.') + 1);

    if (fileExtension.size() != EXTENSION_LENGTH || 
        (fileExtension != "pbm" && fileExtension != "pgm" && fileExtension != "ppm"))
    {
        return ImageType::UNKNOWN;
    }

    std::string firstLine;
    std::getline(file, firstLine);

    file.seekg(0, std::ios::beg);

    std::string magicNumber = "";
    magicNumber.push_back(firstLine[0]);
    magicNumber.push_back(firstLine[1]);

    if ((fileExtension == "pbm" && magicNumber != "P1") ||
        (fileExtension == "pgm" && magicNumber != "P2") ||
        (fileExtension == "ppm" && magicNumber != "P3"))
    {
        throw std::runtime_error("Mismatch between the file extension and the magic number");
    }

    switch (magicNumber[1])
    {
    case '1':
        return ImageType::BITMAP;

    case '2':
        return ImageType::GRAYMAP;

    case '3':
        return ImageType::PIXMAP;
    }

    return ImageType::UNKNOWN;
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

bool ImageEditor::fileExists(std::string path)
{
    std::ifstream file(path.c_str());

    bool result = file.good();
    file.close();

    return result;
}

void ImageEditor::openImage(std::string path)
{
    ImageReader* reader = nullptr;
    ImageType type = this->getTypeOfImage(path);

    switch (type)
    {
    case ImageType::BITMAP:
        reader = new BitMapReader(path);
        break;

    case ImageType::GRAYMAP:
        reader = new GrayMapReader(path);
        break;

    case ImageType::PIXMAP:
        reader = new PixMapReader(path);
        break;

    default:
        throw std::invalid_argument("Invalid image format");
    }

    this->image = reader->loadImage();

    this->getFileName(path);
    std::cout << "Successfully opened " << this->currentFileName << std::endl;

    if (reader)
    {
        delete reader;
    }
}

void ImageEditor::saveImage(std::string path, bool save)
{
    if (save && path.empty())
    {
        throw std::invalid_argument("No file is currently opened");
    }

    if (!save && this->fileExists(path))
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


    ImageConverter converter(this->image);
    Image* newImage = nullptr;

    if (this->image->getType() == ImageType::BITMAP && fileExtension != "pbm")
    {
        if (fileExtension == "pgm")
        {
            newImage = converter.bitMaptoGrayMap();
        }
        else if (fileExtension == "ppm")
        {
            newImage = converter.bitMaptoPixMap();
        }
    }
    else if (this->image->getType() == ImageType::GRAYMAP && fileExtension != "pgm")
    {
        if (fileExtension == "pbm")
        {
            newImage = converter.grayMaptoBitMap();
        }
        else if (fileExtension == "ppm")
        {
            newImage = converter.grayMaptoPixMap();
        }
    }
    else if (this->image->getType() == ImageType::PIXMAP && fileExtension != "ppm")
    {
        if (fileExtension == "pbm")
        {
            newImage = converter.pixMaptoBitMap();
        }
        else if (fileExtension == "pgm")
        {
            newImage = converter.pixMaptoGrayMap();
        }
    }

    if (newImage)
    {
        if (this->image)
        {
            delete this->image;
        }
        this->image = newImage;
    }


    ImageWriter* writer = nullptr;

    switch (this->image->getType())
    {
    case ImageType::BITMAP:
        writer = new BitMapWriter(path, this->image);
        break;

    case ImageType::GRAYMAP:
        writer = new GrayMapWriter(path, this->image);
        break;

    case ImageType::PIXMAP:
        writer = new PixMapWriter(path, this->image);
        break;
    }

    writer->saveImage();
    this->unsavedChanges = false;
    this->getFileName(path);

    std::cout << "Successfully saved " << this->currentFileName << std::endl;

    if (writer)
    {
        delete writer;
    }
}

void ImageEditor::createImage(unsigned int width, unsigned int height, std::string hexColor)
{
    this->image = new Image(width, height, hexColor);
    this->currentFileName = "";
    this->unsavedChanges = true;
    std::cout << "Created new document with size " << width << "x" << height << " and filled with " <<  hexColor << std::endl;
}

void ImageEditor::errorDiffusionDithering(ErrorDiffusionAlrogithmType alrorithm)
{
    ErrorDiffusionAlgorithm* alg = nullptr;
    
    switch (alrorithm)
    {
    case ErrorDiffusionAlrogithmType::BASIC_ONE_DIMENSIONAL:
        alg = new BasicOneDimensional(this->image);
        break;

    case ErrorDiffusionAlrogithmType::BASIC_TWO_DIMENSIONAL:
        alg = new BasicTwoDimensional(this->image);
        break;

    case ErrorDiffusionAlrogithmType::FLOYD_STEINBERG:
        alg = new FloydSteinberg(this->image);
        break;

    case ErrorDiffusionAlrogithmType::FLOYD_STEINBERG_FALSE:
        alg = new FloydSteinbergFalse(this->image);
        break;

    case ErrorDiffusionAlrogithmType::JARVIS_JUDICE_NINKE:
        alg = new JarvisJudiceNinke(this->image);
        break;

    case ErrorDiffusionAlrogithmType::STUCKI:
        alg = new Stucki(this->image);
        break;

    case ErrorDiffusionAlrogithmType::ATKINSON:
        alg = new Atkinson(this->image);
        break;

    case ErrorDiffusionAlrogithmType::BURKES:
        alg = new Burkes(this->image);
        break;

    case ErrorDiffusionAlrogithmType::SIERRA:
        alg = new Sierra(this->image);
        break;

    case ErrorDiffusionAlrogithmType::SIERRA_TWO_ROWS:
        alg = new SierraTwoRows(this->image);
        break;

    case ErrorDiffusionAlrogithmType::SIERRA_LITE:
        alg = new SierraLite(this->image);
        break;
    
    default:
        throw std::invalid_argument("Invalid algorithm");
    }

    Image* newImage = alg->dither();
    if (this->image)
    {
        delete this->image;
    }
    this->image = newImage;
    this->unsavedChanges = true;

    std::cout << "Successfully dithered " << this->currentFileName << std::endl;

    if (alg)
    {
        delete alg;
    }
}

void ImageEditor::orderedDithering(OrderedDitheringAlgorithmType algorithm)
{
    OrderedDitheringAlgorithm* alg = nullptr;
    
    if (algorithm == OrderedDitheringAlgorithmType::FOUR_X_FOUR_BAYER_MATRIX)
    {
        alg = new FourXFour(this->image);
    }
    else if (algorithm == OrderedDitheringAlgorithmType::EIGHT_X_EIGHT_BAYER_MATRIX)
    {
        alg = new EightXEight(this->image);
    }
    else
    {
        throw std::invalid_argument("Invalid algorithm");
    }

    Image* newImage = alg->dither();
    if (this->image)
    {
        delete this->image;
    }
    this->image = newImage;
    this->unsavedChanges = true;

    std::cout << "Successfully dithered " << this->currentFileName << std::endl; 

    if (alg)
    {
        delete alg;
    }
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