/** @file imageWriter.h
 *  @brief A class for writing images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "image.h"
#include "enums.h"
#include "imageOpener.h"
#include <string>

/**
 * @class ImageWriter
 * @note inherits ImageOpener
 */
class ImageWriter : public ImageOpener
{
protected:
    Image* image; //!< stores a pointer to the image which will be saved into file

    //! Constructor with parameters
    ImageWriter(std::string path, Image* image);

public:
    //! Pure virtual function which is inherited
    virtual void saveImage() = 0;

    //! Default virtual destructor
    virtual ~ImageWriter() = default; 
};