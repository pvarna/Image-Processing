#pragma once

#include "image.h"
#include <vector>

class GrayMap : public Image
{
private:
    unsigned int maxValue;
    std::vector<unsigned int> pixels;

public:
    GrayMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<unsigned int> pixels);

    virtual void print() override;
    //virtual void write(std::string path) override;

    unsigned int getMaxValue() const;
    unsigned int operator [] (std::size_t index) const;
};