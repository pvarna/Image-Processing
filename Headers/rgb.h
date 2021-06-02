#pragma once

#include <cstdint>
#include <string>

struct RGB
{
public:
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    RGB();
    RGB(unsigned int red, unsigned int green, unsigned int blue);
    RGB(std::string hexCode);

    friend std::ostream& operator << (std::ostream& out, const RGB& color);

private:
    char charToUpper(char ch);
    std::string stringToUpper(std::string str);

    bool isDigit(char ch);
    bool isHexLetter(char ch);

    unsigned int hexToDecimal(std::string hex);
};
