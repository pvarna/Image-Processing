/** @file grayMapReader.h
 *  @brief A class for reading PGM images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageReader.h"

/**
 * @class GrayMapReader
 * @note inherits ImageReader
 */
class GrayMapReader : public ImageReader
{
public:
    //! Constructor with parameter
    GrayMapReader(std::string path);

    //! Function for loading a GrayMap image (overrides the function from the parent class)
    Image* loadImage() override; 
};