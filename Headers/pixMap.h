#pragma once

#include "image.h"
#include "rgb.h"
#include "consts.h"
#include <vector>
#include <string>

class PixMap : public Image
{
private:
    unsigned int maxValue;
    std::vector<RGB> pixels;

public:
    PixMap(unsigned int width, unsigned int height, unsigned int maxValue, std::vector<RGB> pixels);
    PixMap(unsigned int width, unsigned int height, std::string hexCode);

    virtual void print() override;
    //virtual void write(std::string path) override;

    unsigned int getMaxValue() const;
    RGB operator [] (std::size_t index) const;

    ~PixMap();
};