#pragma once
#include "imageEditor.h"
#include "commandLine.h"
#include "consts.h"

class ImageProcessor
{
private:
    static std::string validCommands[NUMBER_OF_COMMANDS];

    ImageEditor editor; 
    bool stopProgram;

    bool isValid(CommandLine command); 
    
    bool isDigit(char ch);
    bool isNumber(std::string str);

    void printHelp();
    void printDitheringAlgorithms();

public:
    ImageProcessor();

    void execute(CommandLine command);
    void start();
};