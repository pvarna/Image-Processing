#pragma once

#include <cstdint>
#include <string>

struct RGB
{
public:
    int red;
    int green;
    int blue;

    RGB();
    RGB(int red, int green, int blue);
    RGB(std::string hexCode);

    friend std::ostream& operator << (std::ostream& out, const RGB& color);

private:
    char charToUpper(char ch);
    std::string stringToUpper(std::string str);

    bool isDigit(char ch);
    bool isHexLetter(char ch);

    int hexToDecimal(std::string hex);
};
