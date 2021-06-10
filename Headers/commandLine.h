#pragma once

#include "consts.h"
#include <vector>
#include <string>
#include <cstddef>

class CommandLine
{
private:
    // static std::string validCommandsOneArgument[NUMBER_OF_COMMANDS_WITH_ONE_ARGUMENT];
    // static std::string validCommandsTwoArguments[NUMBER_OF_COMMANDS_WITH_TWO_ARGUMENTS];
    // static std::string validCommandsThreeArguments[NUMBER_OF_COMMANDS_WITH_THREE_ARGUMENTS];
    // static std::string validCommandsFourArguments[NUMBER_OF_COMMANDS_WITH_FOUR_ARGUMENTS];
    // static std::string validCommandsFiveArguments[NUMBER_OF_COMMANDS_WITH_FIVE_ARGUMENTS];
    // std::string mainCommand = "";
    // std::string secondArgument = "";
    // std::string thirdArgument = "";
    // std::string fourthArgument = "";
    // std::string fifthArgument = "";
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

    // std::string getMainCommand() const;
    // std::string getSecondArgument() const;
    // std::string getThirdArgument() const;
    // std::string getFourthArgument() const;
    // std::string getFifthArgument() const;

    std::size_t getSize() const;
    std::string& operator [] (std::size_t index);
};