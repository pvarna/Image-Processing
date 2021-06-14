/** @file basicTwoDimensional.h
 *  @brief A class for dithering images via Basic Two-Dimensional Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class BasicTwoDimensional
 * @note inherits ErrorDiffusionAlgorithm
 */
class BasicTwoDimensional : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Basic Two-Dimensional algorithm

public:
    //! Constructor with parameter
    BasicTwoDimensional(Image* image);
};