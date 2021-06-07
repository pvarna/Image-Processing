#pragma once

enum class ImageType
{
    UNKNOWN = -1,
    BITMAP,
    GRAYMAP,
    PIXMAP
};

enum class ErrorDiffusionAlrogithm
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