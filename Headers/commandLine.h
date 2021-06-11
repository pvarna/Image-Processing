#pragma once

#include "consts.h"
#include <vector>
#include <string>
#include <cstddef>

class CommandLine
{
private:
    std::vector<std::string> arguments;

    std::size_t getNumberOfQuotes(std::string string);
    std::string stringToUpper(std::string& string);
    void removeExtraWhitespaces(std::string& string);
    void removeEmptyArguments(std::vector<std::string>& arguments);
    void parseCommandLine(std::string commandLine);
    bool isMainCommandValid(std::string command);
    bool isNumberOfArgumentsCorrect(std::vector<std::string> arguments);

public:
    CommandLine(std::string commandLine);

    std::size_t getSize() const;
    std::string& operator [] (std::size_t index);
};