/** @file floydSteinberg.h
 *  @brief A class for dithering images via Floyd Steinberg Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class FloydSteinberg
 * @note inherits ErrorDiffusionAlgorithm
 */
class FloydSteinberg : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the FloydSteinberg algorithm

public:
    //! Constructor with parameter
    FloydSteinberg(Image* image);
};