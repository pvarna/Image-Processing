/** @file pixMapWriter.h
 *  @brief A class for writing PixMap images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageWriter.h"

/**
 * @class PixMapWriter
 * @note inherits ImageWriter
 */
class PixMapWriter : public ImageWriter
{
public:
    //! Constructor with parameters
    PixMapWriter(std::string path, Image* image);

    //! Function for saving a PixMap image into file (overrides the function from the parent class)
    void saveImage() override;
};