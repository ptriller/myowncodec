#include "EncodedFrame.h"
#include "VideoFrame.h"
#include "VideoStream.h"
#include "base.h"

EncodedFrame::EncodedFrame(std::uint32_t frameType, std::uint64_t timestamp,
                           std::vector<std::uint8_t> &&data) :
        _frameType(frameType), _timestamp(timestamp), _data(std::move(data)) {
}

EncodedFrame::~EncodedFrame() {

}


/**
 * You pass the control over the data ptr to this class and it will clean up.
 */
VideoFrame::VideoFrame(std::uint32_t width, std::uint32_t height, std::uint64_t timestamp,
                       std::vector<std::uint8_t> &&_data) :
        _width(width), _height(height), _timestamp(timestamp), _data(_data) {
    if (_data.size() != _width * _height * 3) {
        throw std::invalid_argument("Size of data vector is wrong !");
    }
}

/**
 * YOu pass the control over the data ptr to this class and it will clean up.
 */
VideoFrame::VideoFrame(std::uint32_t width, std::uint32_t height, std::uint64_t timestamp) :
        _width(width), _height(height), _timestamp(timestamp), _data(
        width * height * 3) {
}

/**
 * dtor.
 */
VideoFrame::~VideoFrame() {
}


VideoStream::~VideoStream() {
}
