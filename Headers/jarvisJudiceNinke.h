/** @file jarvisJudiceNinke.h
 *  @brief A class for dithering images via Jarvis, Judice amd Ninke Algorithm
 *  @note All formulas are from here - https://tannerhelland.com/2012/12/28/dithering-eleven-algorithms-source-code.html
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "errorDiffusionAlgorithm.h"

/**
 * @class JarvisJudiceNinke
 * @note inherits ErrorDiffusionAlgorithm
 */
class JarvisJudiceNinke : public ErrorDiffusionAlgorithm
{
private:
    static int coefficientTable[COEFFIIENT_TABLE_HEIGHT][COEFFIIENT_TABLE_WIDTH]; //!< stores the coefficients for the Floyd Steinberg False algorithm

public:
    //! Constructor with parameter 
    JarvisJudiceNinke(Image* image);
};