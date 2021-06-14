/** @file enums.h
 *  @brief Enum classes for the different types of images and algorithms
 * 
 *  @author Peter Kolev
 */

#pragma once

/**
 * @class ImageType
 */
enum class ImageType
{
    UNKNOWN = -1,
    BITMAP,
    GRAYMAP,
    PIXMAP
};

/**
 * @class ErrorDiffusionAlrogithmType
 */
enum class ErrorDiffusionAlrogithmType
{
    UNKNOWN = -1,
    BASIC_ONE_DIMENSIONAL,
    BASIC_TWO_DIMENSIONAL,
    FLOYD_STEINBERG,
    FLOYD_STEINBERG_FALSE,
    JARVIS_JUDICE_NINKE,
    STUCKI,
    ATKINSON,
    BURKES,
    SIERRA,
    SIERRA_TWO_ROWS,
    SIERRA_LITE
};

/**
 * @class OrderedDitheringAlgorithmType
 */
enum class OrderedDitheringAlgorithmType
{
    UNKNOWN = -1,
    FOUR_X_FOUR_BAYER_MATRIX,
    EIGHT_X_EIGHT_BAYER_MATRIX
};