/** @file pixMapReader.h
 *  @brief A class for reading PPM images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageReader.h"

/**
 * @class PixMapReader
 * @note inherits ImageReader
 */
class PixMapReader : public ImageReader
{
public:
    //! Constructor with parameter
    PixMapReader(std::string path);

    //! Function for loading a PixMap image (overrides the function from the parent class)
    Image* loadImage() override; 
};