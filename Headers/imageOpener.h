/** @file imageOpener.h
 *  @brief A class for opening text files
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "enums.h"
#include <fstream>
#include <string>

/**
 * @class ImageOpener
 */
class ImageOpener
{
protected:
    std::fstream file; //!< stores the stream

    //! Constructor with parameters, opens a file with fixed path and fixed mode (in/out)
    ImageOpener(std::string path, std::ios::openmode mode);

public:
    //! Destructor which closes the file
    ~ImageOpener();
};