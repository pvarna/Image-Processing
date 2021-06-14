/** @file imageReader.h
 *  @brief A class for reading images
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "image.h"
#include "enums.h"
#include "imageOpener.h"
#include <string>
#include <vector>

/**
 * @class ImageReader
 * @note inherits ImageOpener
 */
class ImageReader : public ImageOpener
{
protected:
    static const std::size_t MAGIC_NUMBER_LENGTH = 2; //!< a const for the length of the magic number of the image
    static const unsigned int DEFAULT_MAX_VALUE = 255; //!< a const for the default max value of the pixel
    static const std::size_t BITMAP_METADATA_COUNT = 2; //!< a const for the count of metadata values of BitMap images 
    static const std::size_t GRAYMAP_PIXMAP_METADATA_COUNT = 3; //!< a const for the count of metadata values of GrayMap and PixMap images

    std::vector<std::string> data; //!< stores all data written from the file (metadata + pixels) excluding comments

    //! Helper function for checking if a char is a digit
    bool isDigit(char ch);
    
    //! Helper function for checking if a string is an unsigned number
    bool isNumber(std::string string);

    //! Helper function for removing extra wgitespaces from a string
    void removeExtraWhitespaces(std::string& string);

    //! Helper function fot parsing a string into separate words
    std::vector<std::string> parseString(std::string string);

    //! Main function for reading the data from a file
    void readData();

    //! Constructor with parameter
    ImageReader(std::string path);

public:
    //! Pure virtual function which is inherited
    virtual Image* loadImage() = 0;

    //! Default virtual destructor
    virtual ~ImageReader() = default;
};