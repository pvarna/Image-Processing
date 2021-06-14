/** @file eightXEight.h
 *  @brief A class for dithering images via 8x8 Bayer matrix
 *  @note All coefficients are from here - https://en.wikipedia.org/wiki/Ordered_dithering
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "orderedDitheringAlgorithm.h"

/**
 * @class EightXEight
 * @note inherits OrderedDitheringAlgorithm
 */
class EightXEight : public OrderedDitheringAlgorithm
{
private:
    static int coefficients[MAX_TABLE_SIDE][MAX_TABLE_SIDE]; //!< stores the values from the 8x8 Bayer table

public:
    //! Constructor with parameter
    EightXEight(Image* image);
};