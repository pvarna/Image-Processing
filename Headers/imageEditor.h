/** @file imageEditor.h
 *  @brief A class for editing an image (opening, closing, saving, dithering, cropping, resizing)
 *  
 *  @author Peter Kolev
 */

#pragma once

#include "image.h"
#include <vector>

/**
 * @class ImageEditor
 */
class ImageEditor
{
private:
    static const std::size_t EXTENSION_LENGTH = 3; //!< a const for the length of the files extension

    Image* image; //!< stores a pointer to the image which will be dithered
    std::vector<int> grayscalePixels; //!< stores the pixels of the image converted into grayscale
    std::string currentFileName; //!< stores the name of the currently opened file
    bool unsavedChanges; //!< shows if there are unsaved changes or not

    //! Helper function for deallocating the allocated memory
    void deallocate();

    //! Gets the type of the image with given path
    ImageType getTypeOfImage(std::string path);

    //! Stores the name of the file (without the full path)
    void getFileName(std::string path);

    //! Checks if a file exists
    bool fileExists(std::string path);

public:
    //! Default constructor
    ImageEditor();

    //! Deleted copy constructor
    ImageEditor(const ImageEditor& other) = delete;

    //! Deleted copy assignment operator
    ImageEditor& operator = (const ImageEditor& other) = delete;

    //! Destructor
    ~ImageEditor();

    //! Gets the name of the currently opened file
    std::string getCurrentFileName() const;

    //! Gets a pointer to the currently opened image
    Image* getImage() const;

    //! Creates an image with fixed width, height and color (hex)
    void createImage(unsigned int width, unsigned int height, std::string hexColor);

    //! Reads the image via ImageReader
    void openImage(std::string path);

    //! Saves the image into file via ImageWriter
    void saveImage(std::string path, bool save);

    //! Closes the currently opened file, returns true if the closure is successfull
    bool close();

    //! Dithers the image via ErrorDiffusionAlrogithm
    void errorDiffusionDithering(ErrorDiffusionAlrogithmType algorithm);

    //! Dithers the image via OrderedDitheringAlgorithm
    void orderedDithering(OrderedDitheringAlgorithmType algorithm);

    //! Crops a rectangle from the image with given coordinates of the upper left and lower right corners
    void crop(int x1, int y1, int x2, int y2);

    //! Resizes the image with fixed new width and height (the dormula is from this site - https://courses.cs.vt.edu/~masc1044/L17-Rotation/ScalingNN.html)
    void resize(unsigned int newWidth, unsigned int newHeight);

    //! Resizes the image with given percentage
    void resize(double percentage);
};