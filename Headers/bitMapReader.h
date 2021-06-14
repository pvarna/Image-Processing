/** @file bitMapReader.h
 *  @brief A class for reading PBM images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageReader.h"

/**
 * @class BitMapReader
 * @note inherits ImageReader
 */
class BitMapReader : public ImageReader
{
private:
    const unsigned int RGB_WHITE = 255; //!< a const for the default value of the white
    const unsigned int RGB_BLACK = 0; //!< a const for the default value of the black

public:
    //! Constructor with parameter
    BitMapReader(std::string path);

    //! Function for loading a BitMap image (overrides the function from the parent class)
    Image* loadImage() override; 
};