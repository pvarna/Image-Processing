/** @file imageConverter.h
 *  @brief A class for converting images between different types
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "image.h"

/**
 * @class ImageConverter
 */
class ImageConverter
{
private:
    Image* image; //!< stores a pointer to the image which will be converted

    //! Helper function for converting RGB values into grayscale
    int RGBToGrayscale(RGB color);

public:
    //! Constructor with parameter
    ImageConverter(Image* image);

    //! Function for converting an image from PBM to PGM
    Image* bitMaptoGrayMap();

    //! Function for converting an image from PBM to PPM
    Image* bitMaptoPixMap();

    //! Function for converting an image from PGM to PBM
    Image* grayMaptoBitMap();

    //! Function for converting an image from PGM to PPM
    Image* grayMaptoPixMap();

    //! Function for converting an image from PPM to PBM
    Image* pixMaptoBitMap();

    //! Function for converting an image from PPM to PGM
    Image* pixMaptoGrayMap();
};