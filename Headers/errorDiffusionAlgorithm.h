/** @file еrrorDiffusionAlgorithm.h
 *  @brief A class for dithering images via 11 error diffusion algorithms
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "image.h"
#include <cstddef>
#include <vector>

/**
 * @class ErrorDiffusionAlgorithm
 */
class ErrorDiffusionAlgorithm
{
protected:
    static const std::size_t COEFFIIENT_TABLE_HEIGHT = 3; //!< a const for the height of the coefficient table
    static const std::size_t COEFFIIENT_TABLE_WIDTH = 5; //!< a const for the width of the coefficient table

    Image* image; //!< stores a pointer to the image which will be dithered
    std::vector<int> grayscalePixels; //!< stores the pixels of the image converted into grayscale
    int table[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficient table used for the algorithm
    bool isShiftable; //!< shows if the divisor is a power of 2
    int divisor; //!< stores the divisor used for the algorithm (if it is a power of 2, the variable stores the power, not the divisor)

    //! Helper function for converting RGB values into grayscale
    int RGBToGrayscale(RGB color);

    //! Function for loading the vector of grayscale pixels from the image using the helper function
    void loadGrayscalePixels();

    //! Function for checking if a value is closer to zero than to the max value
    bool isCloserToZero(int value, int maxValue);

    //! Function for checking if given indexes are inside the image
    bool isInsideTheImage(std::size_t i, std::size_t j, unsigned int height, unsigned int width);
    
    //! Function for spreading the error to the neighbor pixels    
    void spreadError(std::size_t currentI, std::size_t currentJ, unsigned int height, unsigned int width, int error);
    
    //! Function for adding error to a given pixel
    void addError(int& pixel, int error, int coefficient);

    //! Constructor with parameters
    ErrorDiffusionAlgorithm(Image* image, int table[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH], bool isShiftable, int divisor);

public:
    //! Main function for dithering an image via error diffusion
    Image* dither();
};