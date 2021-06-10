#include "../Headers/imageProcessor.h"
#include <iostream>

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
        throw std::invalid_argument("Please try again");
    }

    std::string mainCommand = command[0];
    
    if (mainCommand == "EXIT")
    {
        this->stopProgram = true;
        std::cout << "Exiting the program..." << std::endl;
    }
    else if (mainCommand == "CLOSE")
    {
        this->editor.close();
    }
    else if (mainCommand == "NEW" || mainCommand == "OPEN")
    {
        bool successfullClose = true;
        if (this->editor.getImage())
        {
            successfullClose = this->editor.close();
        }

        if (successfullClose)
        {
            if (mainCommand == "OPEN")
            {
                this->editor.openImage(command[1]);
            }
            else
            {
                this->editor.createImage(std::stoi(command[1]), std::stoi(command[2]), command[3]);
            }
        }
    }
    else if (mainCommand == "SAVE")
    {
        this->editor.saveImage(this->editor.getCurrentFileName());
    }
    else if (mainCommand == "SAVEAS")
    {
        this->editor.saveImage(command[1]);
    }
    else if (mainCommand == "HELP")
    {
        this->printHelp();
    }
    else if (mainCommand == "DITHER")
    {
        
    }
}

// void ImageProcessor::openImage(std::string path)
// {
//     this->reader = new ImageReader(path);

//     if (this->image)
//     {
//         delete this->image;
//     }
//     this->image = this->reader->loadImage();
// }

// void ImageProcessor::saveImage(std::string path)
// {
//     if (!this->image)
//     {
//         throw std::invalid_argument("No image is loaded");
//     }

//     this->writer = new ImageWriter(path, this->image);

//     this->writer->saveImage();
// }

// void ImageProcessor::doDithering()
// {
//     this->editor = new ImageEditor(this->image);

//     if (!this->image)
//     {
//         std::invalid_argument("No image is loaded");
//     }

//     this->image = editor->orderedDithering(OrderedDitheringAlgorithm::EIGHT_X_EIGHT_BAYER_MATRIX);
// }

// void ImageProcessor::crop()
// {
//     this->editor = new ImageEditor(this->image);

//     if (!this->image)
//     {
//         std::invalid_argument("No image is loaded");
//     }

//     this->image = editor->cropImage(100, 100, 300, 300);
// }

// void ImageProcessor::resize()
// {
//     this->editor = new ImageEditor(this->image);

//     if (!this->image)
//     {
//         std::invalid_argument("No image is loaded");
//     }

//     this->image = editor->resize(200);
// }

// ImageProcessor::~ImageProcessor()
// {
//     if (this->image)
//     {
//         delete this->image;
//     }

//     if (this->command)
//     {
//         delete this->command;
//     }

//     if (this->reader)
//     {
//         delete this->reader;
//     }

//     if (this->writer)
//     {
//         delete this->writer;
//     }

//     if (this->editor)
//     {
//         delete this->editor;
//     }
// }