#pragma once

#include <stdexcept>

const std::size_t MAGIC_NUMBER_LENGTH = 2;
const unsigned int DEFAULT_MAX_VALUE = 255;
const std::size_t EXTENSION_LENGTH = 3;
const std::size_t BITMAP_METADATA_COUNT = 2;
const std::size_t GRAYMAP_PIXMAP_METADATA_COUNT = 3;
const std::size_t HEX_CODE_LENGTH = 7;
const unsigned int DIGIT_TO_HEX_LALUE_DIFFERENCE = 48;
const unsigned int LETTER_TO_HEX_LALUE_DIFFERENCE = 55;
const unsigned int RGB_WHITE = 255;
const unsigned int RGB_BLACK = 0;

const std::size_t NUMBER_OF_COMMANDS_WITH_ONE_ARGUMENT = 5;
const std::size_t NUMBER_OF_COMMANDS_WITH_TWO_ARGUMENTS = 3;
const std::size_t NUMBER_OF_COMMANDS_WITH_THREE_ARGUMENTS = 1;
const std::size_t NUMBER_OF_COMMANDS_WITH_FOUR_ARGUMENTS = 1;
const std::size_t NUMBER_OF_COMMANDS_WITH_FIVE_ARGUMENTS = 1;

const std::size_t NUMBER_OF_COMMANDS = 10;

const std::size_t MIN_NUMBER_OF_ARGUMENTS = 1;
const std::size_t MAX_NUMBER_OF_ARGUMENTS = 5;