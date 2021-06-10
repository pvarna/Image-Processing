#include "../Headers/imageProcessor.h"
#include <iostream>
#include <limits>

std::string ImageProcessor::validCommands[NUMBER_OF_COMMANDS] = {"NEW", "OPEN", "CLOSE", "SAVE", "SAVEAS", "EXIT", "HELP", "DITHER", "RESIZE", "CROP"};

ImageProcessor::ImageProcessor() : editor()
{
    this->stopProgram = false;
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
    std::cout << "crop <x1> <y1> <x2> <y2>      " << '\t' << "crops a rectangle with coordinates <x1> <y1> <x2> <y2> from the currently opened image" << std::endl;
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
        if (mainCommand == ImageProcessor::validCommands[i])
        {
            commandFound = true;
            break;
        }
    }

    if (!commandFound)
    {
        std::cout << "Invalid main command" << std::endl;
        return false;
    }

    if (mainCommand == "NEW")
    {
        if (size != 4)
        {
            std::cout << "Invalid number of arguments" << std::endl;
            return false;
        }

        if (!isNumber(command[1]) || !isNumber(command[2]))
        {
            std::cout << "The width and the height must be numbers" << std::endl;
            return false;
        }
    }

    if ((mainCommand == "CLOSE" || mainCommand == "EXIT" || mainCommand == "SAVE" 
        || mainCommand == "HELP" || mainCommand == "DITHER") && size != 1)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return false;
    }

    if ((mainCommand == "OPEN" || mainCommand == "SAVEAS") && size != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return false;
    }

    if (mainCommand == "CROP")
    {
        if (size != 5)
        {
            std::cout << "Invalid number of arguments" << std::endl;
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
        if (size != 3 && size != 2)
        {
            std::cout << "Invalid number of arguments" << std::endl;
            return false;
        }

        if (size == 2 && !isNumber(command[1]))
        {
            std::cout << "The percentage must be a number" << std::endl;
            return false;
        }

        if (size == 3 && (!isNumber(command[1]) || !isNumber(command[2])))
        {
            std::cout << "The width and the height must be numbers" << std::endl;
            return false;
        }
    }

    return true;
}

void ImageProcessor::execute(CommandLine command)
{
    if (!isValid(command))
    {
        return;
    }

    std::string mainCommand = command[0];
    std::size_t size = command.getSize();
    
    if (mainCommand == "EXIT")
    {
        this->stopProgram = true;
        if (this->editor.getImage())
        {
            bool close = this->editor.close();
        }
        std::cout << "Exiting the program..." << std::endl;
    }
    else if (mainCommand == "CLOSE")
    {
        bool close = true;
        if (!this->editor.getImage())
        {
            std::cout << "No image is currently loaded" << std::endl;
            close = false;
        }

        if (close)
        {
            bool close = this->editor.close();
        }
    }
    else if (mainCommand == "NEW")
    {
        bool close = this->editor.close();
        if (close)
        {
            this->editor.createImage(std::stoi(command[1]), std::stoi(command[2]), command[3]);
        }
    }
    else if (mainCommand == "OPEN")
    {
        bool close = this->editor.close();
        if (close)
        {
            this->editor.openImage(command[1]);
        }
    }
    else if (mainCommand == "SAVE")
    {
        if (this->editor.getImage())
        {
            this->editor.saveImage(this->editor.getCurrentFileName(), true);
        }
        else
        {
            throw std::invalid_argument("No file is currently opened");
        }
    }
    else if (mainCommand == "SAVEAS")
    {
        if (this->editor.getImage())
        {
            this->editor.saveImage(command[1], false);
        }
        else
        {
            throw std::invalid_argument("No file is currently opened");
        }
    }
    else if (mainCommand == "HELP")
    {
        this->printHelp();
    }
    else if (mainCommand == "DITHER")
    {
        if (this->editor.getImage())
        {
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

                std::cout << std::endl;
                
                switch (option)
                {
                    case 1:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::BASIC_ONE_DIMENSIONAL);
                        break;

                    case 2:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::BASIC_TWO_DIMENSIONAL);
                        break;

                    case 3:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::FLOYD_STEINBERG);
                        break;

                    case 4:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::FLOYD_STEINBERG_FALSE);
                        break;

                    case 5:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::JARVIS_JUDICE_NINKE);
                        break;

                    case 6:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::STUCKI);
                        break;

                    case 7:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::ATKINSON);
                        break;

                    case 8:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::BURKES);
                        break;

                    case 9:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::SIERRA);
                        break;

                    case 10:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::SIERRA_TWO_ROWS);
                        break;

                    case 11:
                        this->editor.errorDiffusionDithering(ErrorDiffusionAlrogithm::SIERRA_LITE);
                        break;

                    case 12:
                        this->editor.orderedDithering(OrderedDitheringAlgorithm::FOUR_X_FOUR_BAYER_MATRIX);
                        break;

                    case 13:
                        this->editor.orderedDithering(OrderedDitheringAlgorithm::EIGHT_X_EIGHT_BAYER_MATRIX);
                        break;

                    default:
                        std::cout << "Invalid option! Try again!" << std::endl;
                        break;
                }
            } while (option < 1 || option > 13);
        }
        else
        {
            throw std::invalid_argument("No file is currently opened");
        }
    }
    else if (mainCommand == "CROP")
    {
        if (this->editor.getImage())
        {
            this->editor.crop(std::stoi(command[1]), std::stoi(command[2]), std::stoi(command[3]), std::stoi(command[4]));
        }
        else
        {
            throw std::invalid_argument("No file is currently opened");
        }
    }
    else if (mainCommand == "RESIZE")
    {
        if (size == 2)
        {
            if (this->editor.getImage())
            {
                this->editor.resize(std::stoi(command[1]));
            }
            else
            {
                throw std::invalid_argument("No file is currently opened");
            }
        }
        else if (size == 3)
        {
            if (this->editor.getImage())
            {
                this->editor.resize(std::stoi(command[1]), std::stoi(command[2]));
            }
            else
            {
                throw std::invalid_argument("No file is currently opened");
            }
        }
    }
}

void ImageProcessor::start()
{
    while (true)
    {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);

        CommandLine cmd(command);
        try
        {
            this->execute(command);
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }

        if (this->stopProgram)
        {
            break;
        }
    }
}