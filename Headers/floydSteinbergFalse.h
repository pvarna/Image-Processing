/** @file floydSteinbergFalse.h
 *  @brief A class for dithering images via Floyd Steinberg False Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class FloydSteinbergFalse
 * @note inherits ErrorDiffusionAlgorithm
 */
class FloydSteinbergFalse : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Floyd Steinberg False algorithm

public:
    //! Constructor with parameter
    FloydSteinbergFalse(Image* image);
};