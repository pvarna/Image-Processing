/** @file imageProcessor.h
 *  @brief A singleton class for handling the user's commands
 *  
 *  @author Peter Kolev
 */

#pragma once
#include "imageEditor.h"
#include "commandLine.h"

/**
 * @class ImageProcessor
 */
class ImageProcessor
{
private:
    static const std::size_t NUMBER_OF_COMMANDS = 10; //!< a const for the number of valid commands
    static const std::string VALID_COMMANDS[NUMBER_OF_COMMANDS]; //!< list of all valid commands
    static const std::size_t ONE_ARGUMENT = 1; //!< a const for one argument
    static const std::size_t TWO_ARGUMENTS = 2; //!< a const for two arguments
    static const std::size_t THREE_ARGUMENTS = 3; //!< a const for three arguments
    static const std::size_t FOUR_ARGUMENTS = 4; //!< a const for four arguments
    static const std::size_t FIVE_ARGUMENTS = 5; //!< a const for five arguments
    static const std::size_t NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS = 11; //!< a const for the number of error diffusion algorithms
    static const std::size_t NUMBER_OF_ORDERED_DITHERING_ALGORITHMS = 2; //!< a const for the number of ordered algorithms

    ImageEditor editor; //!< does main functionality
    bool stopProgram; //!< shows if the program has to stop

    //! Function for checking if a command is valid
    bool isValid(CommandLine command); 
    

    //! Helper function for checking if a char is a digit
    bool isDigit(char ch);
    
    //! Helper function for checking if a string is an unsigned number
    bool isNumber(std::string string);

    //! Exits the program
    void exit();

    //! Closes the currently opened file
    void close();

    //! Creates new image with given width, height and color (hex)
    void newImage(unsigned int width, unsigned int height, std::string hexCode);

    //! Opens a image from a given path
    void open(std::string path);

    //! Saves the unsaved changes in the same file
    void save();

    //! Saves the unsaved changes in a file with given path
    void saveAs(std::string path);

    //! Dithers an image with one of 13 algorithms 
    void dither();

    //! Crops a rectangle from a image with given coordinates of the upper left and lower right corners
    void crop(int x1, int y1, int x2, int y2);

    //! Resizes the image with fixed new width and height
    void resize(int newWidth, int newHeight);

    //! Resizes the image with given percentage
    void resize(double percentage);

    //! Prints information about all valid commands
    void printHelp();

    //! Prints all dithering algorithms
    void printDitheringAlgorithms();

    //! Default constructor
    ImageProcessor();

public:
    //! Deleted copy constructor
    ImageProcessor(const ImageProcessor& other) = delete;

    //! Deleted copy assignment operator
    ImageProcessor& operator = (const ImageProcessor& other) = delete;

    //! Static function for getting the one and only instance of the class
    static ImageProcessor& getInstance();

    //! Executes the given command
    void execute(CommandLine command);

    //! Executes commands while the command isn't "EXIT"
    void start();
};