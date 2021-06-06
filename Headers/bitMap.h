#pragma once

#include "image.h"
#include <vector>

class BitMap : public Image
{
private:
    std::vector<bool> pixels;

public:
    BitMap(unsigned int width, unsigned int height, std::vector<bool> pixels);

    virtual void print() override;
    //virtual void write(std::string path) override;

    bool operator [] (std::size_t index) const;

    ~BitMap();
};