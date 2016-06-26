//
// Created by ptriller on 26.06.2016.
//

#ifndef MYOWNCODEC_CODECAPI_H_H
#define MYOWNCODEC_CODECAPI_H_H

#include "codecimage.h"
#include <memory>
#include <cstdint>
#include <stdexcept>

namespace codec {
    class VideoFrame {
    public:

        VideoFrame(std::uint64_t timestamp, std::unique_ptr<RGBImage> image)
                :_timestamp(timestamp),_image(std::move(image)) {}

        std::uint64_t timestamp() { return _timestamp; }

        RGBImage &image() { return *_image; }
        const RGBImage &image() const { return *_image; }
    private:
        std::uint64_t _timestamp;
        std::unique_ptr<RGBImage> _image;

    };

    class EncodedFrame {
    public:
        EncodedFrame(std::uint32_t frameType, std::uint64_t timestamp,
                     std::vector<std::uint8_t> &&data): _frameType(frameType),
            _timestamp(timestamp), _data(std::move(data)) {  }

        std::uint32_t frameType() const { return _frameType; }

        std::uint64_t timestamp() const { return _timestamp; }

        const std::vector<std::uint8_t> &data() const { return _data; }

    private:
        std::uint32_t _frameType;
        std::uint64_t _timestamp;
        std::vector<std::uint8_t> _data;
    };


    class VideoStream {
    public:
        virtual ~VideoStream() {};

        virtual void Close() = 0;

        virtual std::unique_ptr<VideoFrame> nextFrame() = 0;

    };

}
#endif //MYOWNCODEC_CODECAPI_H_H
