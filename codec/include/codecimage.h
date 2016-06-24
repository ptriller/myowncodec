//
// Created by ptriller on 24.06.16.
//

#ifndef MYOWNCODEC_CODECIMAGE_H_H
#define MYOWNCODEC_CODECIMAGE_H_H

#include <cstdint>
#include <string>
#include <vector>

namespace codec {


    struct RGBPixel {
        std::uint8_t red;
        std::uint8_t green;
        std::uint8_t blue;
    } __attribute__((packed));

    class RGBImage {
    public:
        RGBImage() { }

        RGBImage(std::uint32_t width, std::uint32_t height) :
                _width(width), _height(height), _data(width * height * 3) { }

        void size(std::uint32_t width, std::uint32_t height) {
            _width = width;
            _height = height;
            _data.resize(width * height * 3);
        }

        RGBPixel &get(std::uint32_t x, std::uint32_t y) {
            return *reinterpret_cast<RGBPixel *>(&_data.at((x + _width * y) * 3));
        }

        const RGBPixel &get(std::uint32_t x, std::uint32_t y) const {
            return *reinterpret_cast<const RGBPixel *>(&_data.at((x + _width * y) * 3));
        }

        const std::vector<std::uint8_t> &data() const { return _data; };

        std::vector<std::uint8_t> &data() { return _data; };

    private:
        std::uint32_t _width;
        std::uint32_t _height;
        std::vector<std::uint8_t> _data;
    };


    class BitmapChannel {
    public:
        BitmapChannel() { }

        BitmapChannel(std::uint32_t width, std::uint32_t height):
        _width(width), _height(height), _data(width * height) { }

        void size(std::uint32_t width, std::uint32_t height) {
            _width = width;
            _height = height;
            _data.resize(width * height);
        }

        std::uint8_t &at(std::uint32_t x, std::uint32_t y) {
            return _data.at(x + _width * y);
        }

        std::uint8_t at(std::uint32_t x, std::uint32_t y) const {
            return _data.at(x + _width * y);
        }

        const std::vector<std::uint8_t> &data() const { return _data; };

        std::vector<std::uint8_t> &data() { return _data; };

    private:
        std::uint32_t _width;
        std::uint32_t _height;
        std::vector<std::uint8_t> _data;
    };

    class CompositeImage {
    public:
        CompositeImage(const std::string &type, const std::uint32_t num = 3): _type(type), _channels(num) {}
        const std::string &type() const { return _type; }
        const BitmapChannel &operator[](size_t idx) const { return _channels.at(idx); }
        BitmapChannel &operator[](size_t idx) { return _channels.at(idx); }
        const BitmapChannel &at(size_t idx) const { return _channels.at(idx); }
        BitmapChannel &at(size_t idx) { return _channels.at(idx); }

    private:
        std::string _type;
        std::vector<BitmapChannel> _channels;
    };
}

#endif //MYOWNCODEC_CODECIMAGE_H_H
