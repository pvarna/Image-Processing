/** @file bitMapWriter.h
 *  @brief A class for writing BitMap images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageWriter.h"

/**
 * @class BitMapWriter
 * @note inherits ImageWriter
 */
class BitMapWriter : public ImageWriter
{
private:
    const unsigned int RGB_WHITE = 255; //!< a const for the default value of the white
    const unsigned int RGB_BLACK = 0; //!< a const for the default value of the black

public:
    //! Constructor with parameters
    BitMapWriter(std::string path, Image* image);

    //! Function for saving a BitMap image into file (overrides the function from the parent class)
    void saveImage() override;
};