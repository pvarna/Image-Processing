#include "../Headers/commandLine.h"
#include <stdexcept>

CommandLine::CommandLine(std::string commandLine)
{
    if (commandLine.length() == 0)
    {
        throw std::invalid_argument("Empty command line!");
    }

    if (getNumberOfQuotes(commandLine) % 2 == 1)
    {
        throw std::invalid_argument("Invalid number of quotes!");
    }

    this->parseCommandLine(commandLine);
}

std::size_t CommandLine::getSize() const
{
    return this->arguments.size();
}

std::size_t CommandLine::getNumberOfQuotes(std::string string)
{
    std::size_t counter = 0;
    std::size_t length = string.length();

    for (std::size_t i = 0; i < length; ++i)
    {
        if (string[i] == '\"')
        {
            ++counter;
        }
    }

    return counter;
}

std::string CommandLine::stringToUpper(std::string string)
{
    std::string result = "";

    std::size_t length = string.length();
    for (std::size_t i = 0; i < length; ++i)
    {
        result.push_back(toupper(string[i]));
    }

    return result;
}

void CommandLine::removeExtraWhitespaces(std::string& string)
{
    std::size_t currentIndex = 0;
    std::size_t length = string.length();

    std::string result = "";

    while (string[currentIndex] == ' ')
    {
        ++currentIndex;
    }

    bool spaceFound = false;

    while (currentIndex < length)
    {
        if (string[currentIndex] != ' ')
        {
            result.push_back(string[currentIndex++]);
            spaceFound = false;
        }
        else
        {
            if (!spaceFound)
            {
                result.push_back(string[currentIndex++]);
                spaceFound = true;
            }
            else
            {
                ++currentIndex;
            }
        }
    }

    if (result.back() == ' ')
    {
        result.pop_back();
    }

    string = result;
}

void CommandLine::removeEmptyArguments(std::vector<std::string>& arguments)
{
    for (std::size_t i = 0; i < arguments.size(); ++i)
    {
        if (arguments[i] == "")
        {
            arguments.erase(arguments.begin() + i);
            --i;
        }
    }
}

void CommandLine::parseCommandLine(std::string commandLine)
{
    removeExtraWhitespaces(commandLine);

    std::size_t length = commandLine.length();
    std::size_t currentIndex = 0;
    std::size_t countWords = 0;

    std::string currentWord = "";

    bool openedQuotes = false;
    while (currentIndex < length)
    {
        if (commandLine[currentIndex] == '\"')
        {
            if (currentIndex == length - 1)
            {
                this->arguments.push_back(currentWord);
                currentWord = "";
                ++countWords;
            }

            openedQuotes = !openedQuotes;
        }
        else if (currentIndex == length - 1 || (!openedQuotes && commandLine[currentIndex] == ' '))
        {
            if (currentIndex == length - 1)
            {
                currentWord.push_back(commandLine[currentIndex]);
            }
            this->arguments.push_back(currentWord);
            currentWord = "";
            ++countWords;
        }
        else
        {
            currentWord.push_back(commandLine[currentIndex]);
        }

        ++currentIndex;
    }

    for (std::size_t i = 0; i < countWords; ++i)
    {
        removeExtraWhitespaces(this->arguments[i]);
    }

    removeEmptyArguments(this->arguments);

    this->arguments[0] = stringToUpper(this->arguments[0]);
}

std::string& CommandLine::operator [] (std::size_t index)
{
    if (index >= this->arguments.size())
    {
        throw std::overflow_error("Invalid index");
    }

    return this->arguments[index];
}