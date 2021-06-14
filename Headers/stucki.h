/** @file stucki.h
 *  @brief A class for dithering images via Stucki Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class Stucki
 * @note inherits ErrorDiffusionAlgorithm
 */
class Stucki : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Stucki algorithm

public:
    //! Constructor with parameter 
    Stucki(Image* image);
};