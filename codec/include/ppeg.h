//
// Created by ptriller on 30.06.16.
//

#ifndef MYOWNCODEC_PPEG_H
#define MYOWNCODEC_PPEG_H

#include "codecimage.h"
#include <cstdint>
#include <vector>

namespace ppeg {

    class ComponentBitmap {
    public:
        void initialize(std::uint32_t width, std::uint32_t height) {
            _width = width;
            _height = height;
            _data.resize(width*height);
        }

        /*
         * No copy, just move
         */
        ComponentBitmap &operator =(ComponentBitmap &arg) = delete;

        ComponentBitmap &operator =(ComponentBitmap &&arg) = default;

        const std::vector<std::uint8_t> &data() const { return _data; }
        std::vector<std::uint8_t> &data() { return _data; }
        std::uint32_t width() const { return _width; };
        std::uint32_t height() const { return _height; };
    private:
        std::uint32_t _width;
        std::uint32_t _height;
        std::vector<std::uint8_t> _data;
    };

    class ComponentImage {
    public:
        ComponentImage(std::uint32_t width, std::uint32_t height, std::uint32_t componentCount) :
                _width(width), _height(height), _components(componentCount) {
        }

        const ComponentBitmap &at(size_t pos) const { return _components.at(pos); }

        const ComponentBitmap &operator[](size_t pos) const { return _components.at(pos); }

        ComponentBitmap &at(size_t pos) { return _components.at(pos); }

        ComponentBitmap &operator[](size_t pos) { return _components.at(pos); }

    private:
        std::uint32_t _width;
        std::uint32_t _height;
        std::vector<ComponentBitmap> _components;
    };


}

#endif //MYOWNCODEC_PPEG_H
