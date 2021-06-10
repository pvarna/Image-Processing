#pragma once

#include "image.h"
#include <vector>

class ImageEditor
{
private:
    Image* image;
    std::vector<int> grayscalePixels;
    std::string currentFileName;
    bool unsavedChanges;

    void deallocate();

    void getFileName(std::string path);

    int RGBToGrayscale(RGB color);

    void loadGrayscalePixels();

    bool isCloserToZero(int value, int maxValue);

    bool isInsideTheImage(std::size_t i, std::size_t j, unsigned int height, unsigned int width);

    void getCoefficientTable(ErrorDiffusionAlrogithm algorithm, int coefficients[3][5], bool& isShiftable, int& divisor);

    void addError(int& pixel, int error, int coefficient, bool isShiftable, int divisor);

    void spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height, unsigned int width, int coefficients[3][5], int error, std::vector<int>& pixels, bool isShiftable, int divisor);

public:
    ImageEditor();
    ImageEditor(const ImageEditor& other) = delete;
    ImageEditor& operator = (const ImageEditor& other) = delete;
    ~ImageEditor();

    std::string getCurrentFileName() const;
    Image* getImage() const;

    void createImage(unsigned int width, unsigned int height, std::string hexColor);
    void openImage(std::string path);
    void saveImage(std::string path);
    bool close();

    void errorDiffusionDithering(ErrorDiffusionAlrogithm algorithm);
    void orderedDithering(OrderedDitheringAlgorithm algorithm);

    void cropImage(int x1, int y1, int x2, int y2);
    void resize(unsigned int newWidth, unsigned int newHeight);
    void resize(double percentage);
};