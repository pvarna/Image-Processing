#include "../Headers/imageProcessor.h"
#include <iostream>
#include <limits>

const std::string ImageProcessor::VALID_COMMANDS[NUMBER_OF_COMMANDS] = 
{"NEW", "OPEN", "CLOSE", "SAVE", "SAVEAS", "EXIT", "HELP", "DITHER", "RESIZE", "CROP"};

ImageProcessor::ImageProcessor() : editor()
{
    this->stopProgram = false;
}

ImageProcessor& ImageProcessor::getInstance()
{
    static ImageProcessor object;

    return object;
}

void ImageProcessor::printHelp()
{
    std::cout << "The following commands are supported: " << std::endl;
    std::cout << "new <width> <height> <hexCode>" << '\t' << "creates new image with size <width>x<heigth> and filled with color <hexCode>" << std::endl;
    std::cout << "open <path>                   " << '\t' << "opens <path>" << std::endl;
    std::cout << "close                         " << '\t' << "closes currently opened image" << std::endl;
    std::cout << "save                          " << '\t' << "saves the currently opened image" << std::endl;
    std::cout << "saveas <path>                 " << '\t' << "saves the currently opened image in <path>" << std::endl;
    std::cout << "help                          " << '\t' << "prints this information" << std::endl;
    std::cout << "dither                        " << '\t' << "dithers the image by 13 algorithms (user's choice)" << std::endl;
    std::cout << "crop <x1> <y1> <x2> <y2>      " << '\t' << "crops a rectangle with coordinates <x1> <y1> (upper left corner) <x2> <y2> (lower right corner) from the currently opened image" << std::endl;
    std::cout << "resize <newWidth> <newHeight> " << '\t' << "resizes the currently opened image setting new dimensions <newWidth> and <newHeight>" << std::endl;   
    std::cout << "resize <percentage>           " << '\t' << "resizes the currently opened image by <percentage>" << std::endl;
    std::cout << "exit                          " << '\t' << "exits the program" << std::endl;
}

void ImageProcessor::printDitheringAlgorithms()
{
    std::cout << "The following dithering algorithms are supported: " << std::endl;
    std::cout << "----- Error-diffusion dithering algorithms -----" << std::endl;
    std::cout << "01. Basic one-dimensional dithering" << std::endl;
    std::cout << "02. Basic two-dimensional dithering" << std::endl;
    std::cout << "03. Floyd-Steinberg dithering" << std::endl;
    std::cout << "04. Floyd-Steinberg False dithering" << std::endl;
    std::cout << "05. Jarvis, Judice, and Ninke dithering" << std::endl;
    std::cout << "06. Stucki dithering" << std::endl;
    std::cout << "07. Atkinson dithering" << std::endl;
    std::cout << "08. Burkes dithering" << std::endl;
    std::cout << "09. Sierra dithering" << std::endl;
    std::cout << "10. Two-Row Sierra dithering" << std::endl;
    std::cout << "11. Sierra Lite dithering" << std::endl;
    std::cout << "--------- Ordered dithering algorithms ---------" << std::endl;
    std::cout << "12. 4x4 dithering" << std::endl;
    std::cout << "13. 8x8 dithering" << std::endl;
}

inline bool ImageProcessor::isDigit(char ch)
{
    return ch >= '0' && ch <= '9';
}

inline bool ImageProcessor::isNumber(std::string str)
{
    std::size_t size = str.size();
    for (std::size_t i = 0; i < size; ++i)
    {  
        if (!this->isDigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

bool ImageProcessor::isValid(CommandLine command)
{
    std::string mainCommand = command[0];
    std::size_t size = command.getSize();
    bool commandFound = false;

    for (std::size_t i = 0; i < NUMBER_OF_COMMANDS; ++i)
    {
        if (mainCommand == ImageProcessor::VALID_COMMANDS[i])
        {
            commandFound = true;
            break;
        }
    }

    if (!commandFound)
    {
        std::cout << "Invalid main command (type \'help\' to see all valid commands)" << std::endl;
        return false;
    }

    if (mainCommand == "NEW")
    {
        if (size != FOUR_ARGUMENTS)
        {
            std::cout << "Invalid number of arguments (type \'help\' to see all valid commands)" << std::endl;
            return false;
        }

        if (!isNumber(command[1]) || !isNumber(command[2]))
        {
            std::cout << "The width and the height must be numbers" << std::endl;
            return false;
        }
    }

    if ((mainCommand == "CLOSE" || mainCommand == "EXIT" || mainCommand == "SAVE" 
        || mainCommand == "HELP" || mainCommand == "DITHER") && size != ONE_ARGUMENT)
    {
        std::cout << "Invalid number of arguments (type \'help\' to see all valid commands)" << std::endl;
        return false;
    }

    if ((mainCommand == "OPEN" || mainCommand == "SAVEAS") && size != TWO_ARGUMENTS)
    {
        std::cout << "Invalid number of arguments (type \'help\' to see all valid commands)" << std::endl;
        return false;
    }

    if (mainCommand == "CROP")
    {
        if (size != FIVE_ARGUMENTS)
        {
            std::cout << "Invalid number of arguments (type \'help\' to see all valid commands)" << std::endl;
            return false;
        }

        if (!isNumber(command[1]) || !isNumber(command[2]) || !isNumber(command[3]) || !isNumber(command[4]))
        {
            std::cout << "The indexes must be numbers" << std::endl;
            return false;
        }
    }

    if (mainCommand == "RESIZE")
    {
        if (size != THREE_ARGUMENTS && size != TWO_ARGUMENTS)
        {
            std::cout << "Invalid number of arguments (type \'help\' to see all valid commands)" << std::endl;
            return false;
        }

        if (size == TWO_ARGUMENTS && !isNumber(command[1]))
        {
            std::cout << "The percentage must be a number" << std::endl;
            return false;
        }

        if (size == THREE_ARGUMENTS && (!isNumber(command[1]) || !isNumber(command[2])))
        {
            std::cout << "The width and the height must be numbers" << std::endl;
            return false;
        }
    }

    return true;
}

void ImageProcessor::exit()
{
    this->stopProgram = true;
    if (this->editor.getImage())
    {
        bool close = this->editor.close();
    }
    std::cout << "Exiting the program..." << std::endl;
}

void ImageProcessor::close()
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No image is currently loaded");
    }

    bool close = this->editor.close();
}

void ImageProcessor::newImage(unsigned int width, unsigned int height, std::string hexCode)
{
    if (this->editor.close())
    {
        this->editor.createImage(width, height, hexCode);
    }
}

void ImageProcessor::open(std::string path)
{
    if (this->editor.close())
    {
        this->editor.openImage(path);
    }
}

void ImageProcessor::save()
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }
    
    this->editor.saveImage(this->editor.getCurrentFileName(), true);
}

void ImageProcessor::saveAs(std::string path)
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }
    
    this->editor.saveImage(path, false);
}

void ImageProcessor::dither()
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }

    int option;
    this->printDitheringAlgorithms();

    do
    {
        std::cout << "Please choose an option: ";
        std::cin >> option;
        while (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number: ";
            std::cin >> option;
        }
        std::cin.ignore();
        
        if (option > 0 && option <= NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS)
        {
            this->editor.errorDiffusionDithering(static_cast<ErrorDiffusionAlrogithmType>(option-1));
        }
        else if (option > NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS && option <= NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS + NUMBER_OF_ORDERED_DITHERING_ALGORITHMS)
        {
            this->editor.orderedDithering(static_cast<OrderedDitheringAlgorithmType>(option-NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS-1));
        }
        else
        {
            std::cout << "Invalid option! Try again!" << std::endl;
        }

    } while (option < 1 || option > NUMBER_OF_ERROR_DIFFUSION_ALGORITHMS + NUMBER_OF_ORDERED_DITHERING_ALGORITHMS);
}

void ImageProcessor::crop(int x1, int y1, int x2, int y2)
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }
    
    this->editor.crop(x1, y1, x2, y2);
}

void ImageProcessor::resize(int newWidth, int newHeight)
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }

    this->editor.resize(newWidth, newHeight);
}

void ImageProcessor::resize(double percentage)
{
    if (!this->editor.getImage())
    {
        throw std::invalid_argument("No file is currently opened");
    }

    this->editor.resize(percentage);
}

void ImageProcessor::execute(CommandLine command)
{
    if (!isValid(command))
    {
        return;
    }

    std::string mainCommand = command[0];
    std::size_t size = command.getSize();
    
    if (mainCommand == "HELP")
    {
        this->printHelp();
    }
    else if (mainCommand == "EXIT")
    {
        this->exit();
    }
    else if (mainCommand == "CLOSE")
    {
        this->close();
    }
    else if (mainCommand == "NEW")
    {
        this->newImage(std::stoi(command[1]), std::stoi(command[2]), command[3]);
    }
    else if (mainCommand == "OPEN")
    {
        this->open(command[1]);
    }
    else if (mainCommand == "SAVE")
    {
        this->save();
    }
    else if (mainCommand == "SAVEAS")
    {
        this->saveAs(command[1]);
    }
    else if (mainCommand == "DITHER")
    {
        this->dither();   
    }
    else if (mainCommand == "CROP")
    {
        this->crop(std::stoi(command[1]), std::stoi(command[2]), std::stoi(command[3]), std::stoi(command[4]));
    }
    else if (mainCommand == "RESIZE")
    {
        if (size == 2)
        {
            this->resize(std::stoi(command[1]));
        }
        else if (size == 3)
        {
            this->resize(std::stoi(command[1]), std::stoi(command[2]));
        }
    }
}

void ImageProcessor::start()
{
    while (!this->stopProgram)
    {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);

        CommandLine cmd(command);
        try
        {
            this->execute(command);
        }
        catch(const std::bad_alloc& ba)
        {
            std::cout << "Memory problem" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}