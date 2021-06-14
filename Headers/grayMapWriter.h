/** @file grayMapWriter.h
 *  @brief A class for writing GrayMap images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "imageWriter.h"

/**
 * @class GrayMapWriter
 * @note inherits ImageWriter
 */
class GrayMapWriter : public ImageWriter
{
public:
    //! Constructor with parameters
    GrayMapWriter(std::string path, Image* image);

    //! Function for saving a GrayMap image into file (overrides the function from the parent class)
    void saveImage() override;
};