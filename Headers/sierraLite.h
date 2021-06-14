/** @file sierraLite.h
 *  @brief A class for dithering images via Sierra Lite Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class SierraLite
 * @note inherits ErrorDiffusionAlgorithm
 */
class SierraLite : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Sierra Lite algorithm

public:
    //! Constructor with parameter
    SierraLite(Image* image);
};