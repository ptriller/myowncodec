//
// Created by ptriller on 22.06.16.
//

#ifndef MYOWNCODEC_COMPONENTIMAGE_H
#define MYOWNCODEC_COMPONENTIMAGE_H

#include <vector>
#include <cstdint>
#include <string>

struct ComponentBitmap {

    void initialize(std::uint32_t width, std::uint32_t height,
                    std::uint32_t scaleWidth, std::uint32_t scaleHeight) {
        this->width = width;
        this->height = height;
        this->scaleHeight = scaleHeight;
        this->scaleWidth = scaleWidth;
        data.resize(width*height);
    }

    std::string type;
    std::uint32_t width;
    std::uint32_t height;
    std::uint32_t scaleWidth;
    std::uint32_t scaleHeight;
    std::vector<std::uint8_t> data;
};

class ComponentImage {
public:
    ComponentImage(const std::string type, std::size_t components = 3): _type(type), bitmaps(components) { }
    ~ComponentImage() {}
    ComponentBitmap & operator[](std::size_t idx) { return bitmaps.at(idx); }
    const ComponentBitmap & operator[](std::size_t idx) const { return bitmaps.at(idx); }
    const std::string & type() { return _type; }

private:
    std::string _type;
    std::vector<ComponentBitmap> bitmaps;
};


#endif //MYOWNCODEC_COMPONENTIMAGE_H
