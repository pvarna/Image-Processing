/** @file fourXFour.h
 *  @brief A class for dithering images via 4x4 Bayer matrix
 *  @note All coefficients are from here - https://en.wikipedia.org/wiki/Ordered_dithering
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "orderedDitheringAlgorithm.h"

/**
 * @class FourXFour
 * @note inherits OrderedDitheringAlgorithm
 */
class FourXFour : public OrderedDitheringAlgorithm
{
private:
    static int coefficients[MAX_TABLE_SIDE][MAX_TABLE_SIDE]; //!< stores the values from the 4x4 Bayer table

public:
    //! Constructor with parameter
    FourXFour(Image* image);
};