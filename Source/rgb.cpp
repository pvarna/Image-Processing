#include "../Headers/rgb.h"

#include <cstddef>
#include <cmath>
#include <iostream>

RGB::RGB()
{
    this->red = 0;
    this->green = 0;
    this->blue = 0;
}

RGB::RGB(int red, int green, int blue)
{
    if (red > DEFAULT_MAX_VALUE || green > DEFAULT_MAX_VALUE || blue > DEFAULT_MAX_VALUE)
    {
        std::cout << red << " " << green << " " << blue << std::endl;
        throw std::invalid_argument("Invalid color value");
    }

    this->red = red;
    this->green = green;
    this->blue = blue;
}

char RGB::charToUpper(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        ch -= ('a' - 'A');
    }

    return ch;
}

std::string RGB::stringToUpper(std::string str)
{
    std::size_t strSize = str.size();

    for (std::size_t i = 0; i < strSize; ++i)
    {
        str[i] = this->charToUpper(str[i]);
    }

    return str; 
}

RGB::RGB(std::string hexCode)
{
    std::size_t size = hexCode.size();

    if (hexCode[0] != '#' || size != HEX_CODE_LENGTH)
    {
        throw std::invalid_argument("Invalid hex code");
    }

    for (std::size_t i = 1; i < size; ++i)
    {
        if (!isDigit(hexCode[i]) && !isHexLetter(hexCode[i]))
        {
            std::cout << hexCode[i] << std::endl;
            throw std::invalid_argument("Invalid hex code");
        }
    }

    this->red = this->hexToDecimal(hexCode.substr(1, 2));
    this->green = this->hexToDecimal(hexCode.substr(3, 2));
    this->blue = this->hexToDecimal(hexCode.substr(5, 2));
}

inline bool RGB::isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

inline bool RGB::isHexLetter(char ch)
{
    ch = this->charToUpper(ch);

    return ch >= 'A' && ch <= 'F';
}

int RGB::hexToDecimal(std::string hex)
{
    std::size_t hexSize = hex.size();
    hex = this->stringToUpper(hex);
    double decimal = 0;

    for (std::size_t i = 0; i < hexSize; ++i)
    {
        char current = hex[i];
        int currentValue;

        if (this->isDigit(hex[i]))
        {
            currentValue = current - DIGIT_TO_HEX_VALUE_DIFFERENCE;
        }
        else if (this->isHexLetter(hex[i]))
        {
            currentValue = current - LETTER_TO_HEX_VALUE_DIFFERENCE;
        }

        decimal += currentValue * pow(16, (hexSize - i - 1));
    }

    int result = static_cast<int>(decimal);
        
    return result;
}

std::ostream& operator << (std::ostream& out, const RGB& color)
{
    out << color.red << " " << color.green << " " << color.blue;

    return out;
}