/** @file sierra.h
 *  @brief A class for dithering images via Sierra Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class Sierra
 * @note inherits ErrorDiffusionAlgorithm
 */
class Sierra : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Sierra algorithm

public:
    //! Constructor with parameter 
    Sierra(Image* image);
};