/** @file basicOneDimensional.h
 *  @brief A class for dithering images via Basic One-Dimensional Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class BasicOneDimensional
 * @note inherits ErrorDiffusionAlgorithm
 */
class BasicOneDimensional : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Basic One-Dimensional algorithm

public:
    //! Constructor with parameter
    BasicOneDimensional(Image* image);
};