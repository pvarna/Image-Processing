/** @file rgb.h
 *  @brief A structure that stores data about a pixel which has three values - red, green and blue
 *  
 *  @author Peter Kolev
 */

#pragma once

#include <cstdint>
#include <string>

/**
 * @struct RGB
 */
struct RGB
{
public:
    int red; //!< stores the red value of the pixel
    int green; //!< stores the green value of the pixel
    int blue; //!< stores the blue value of the pixel

    //! Default constructor, the default values are (0,0,0)
    RGB();

    //! Constructor with fixed values for the different colors
    RGB(int red, int green, int blue);

    //! Constructor with given color in hex
    RGB(std::string hexCode);

    //! Friend function, overloading operator << 
    friend std::ostream& operator << (std::ostream& out, const RGB& color);

private:
    static const unsigned int DEFAULT_MAX_VALUE = 255; //!< a const for the default max value of the pixel
    static const std::size_t HEX_CODE_LENGTH = 7; //!< a const for the length of the hex code
    static const unsigned int DIGIT_TO_HEX_VALUE_DIFFERENCE = 48; //!< a const for the difference between a digit and hex code 
    static const unsigned int LETTER_TO_HEX_VALUE_DIFFERENCE = 55; //!< a const for the difference between a letter (A-F) and hex code

    //! Helper function for converting a lowercase letter to uppercase letter
    char charToUpper(char ch);

    //! Helper function for converting a lowercase word to uppercase word
    std::string stringToUpper(std::string str);

    //! Helper function for checking if a char is a digit
    bool isDigit(char ch);

    //! Helper function for checking if a char is a hex letter (A-F)
    bool isHexLetter(char ch);

    //! Helper function for converting a hex to decimal
    int hexToDecimal(std::string hex);
};
