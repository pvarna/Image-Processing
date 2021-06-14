/** @file commandLine.h
 *  @brief A class for parsing a command line into main command and arguments
 *  
 *  @author Peter Kolev
 */

#pragma once


#include <vector>
#include <string>
#include <cstddef>

/**
 * @class CommandLine
 */
class CommandLine
{
private:
    std::vector<std::string> arguments; //!< stores the resultng main command and arguments

    //! Helper function for getting the number of quotes in a string
    std::size_t getNumberOfQuotes(std::string string);

    //! Helper function for converting a lowercase word to uppercase word
    std::string stringToUpper(std::string string);

    //! Helper function for removing extra whitespaces
    void removeExtraWhitespaces(std::string& string);

    //! Helper function for removing empty strings from a vector
    void removeEmptyArguments(std::vector<std::string>& arguments);

    //! Main function for parsing the command line into different arguments
    void parseCommandLine(std::string commandLine);
    
public:
    //! Constructor with parameter
    CommandLine(std::string commandLine);

    //! Gets the number of arguments of the command line
    std::size_t getSize() const;

    //! Returns reference to a specific argument
    std::string& operator [] (std::size_t index);
};