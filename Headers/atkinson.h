/** @file atkinson.h
 *  @brief A class for dithering images via Atkinson Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class Atkinson
 * @note inherits ErrorDiffusionAlgorithm
 */
class Atkinson : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Atkinson algorithm

public:
    //! Constructor with parameter 
    Atkinson(Image* image);
};