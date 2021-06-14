/** @file image.h
 *  @brief A class that stores data about a PNM image (PBM, PGM or PPM)
 *  
 *  @author Peter Kolev
 */

#pragma once


#include "rgb.h"
#include "enums.h"
#include <vector>
#include <string>

/**
 * @class Image
 */
class Image
{
private:
    static const unsigned int DEFAULT_MAX_VALUE = 255; //!< a const for the default max value of the pixel

    ImageType type; //!< stores the type of the image
    unsigned int width; //!< stores the width of the image
    unsigned int height; //!< stores the height of the image
    unsigned int maxValue; //!< stores the max value of the pixels of the image
    std::vector<RGB> pixels; //!< stored the pixels of the image

public:
    //! Constructor with parameters
    Image(ImageType type, unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels);
    
    //! Constructor with parameters, fills the image with fixec color (hex)
    Image(unsigned int width, unsigned int height, std::string hexCode);

    //! Gets the type of the image (BitMap, GrayMap, PixMap)
    ImageType getType() const;

    //! Gets the width of the image
    unsigned int getWidth() const;

    //! Gets the height of the image
    unsigned int getHeight() const;

    //! Gets the max value of the pixels of the image
    unsigned int getMaxValue() const;

    //! Sets new type of the image
    void setType(ImageType type);

    //! Returns reference to a specific pixel
    RGB& operator [] (std::size_t index);
};