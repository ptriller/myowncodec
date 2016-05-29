#include "EncodedFrame.h"
#include "VideoFrame.h"
#include "VideoStream.h"
#include "base.h"

EncodedFrame::EncodedFrame(unsigned int frameType, unsigned long timestamp,
		std::vector<unsigned char> &&data) :
		_frameType(frameType), _timestamp(timestamp), _data(data) {
}

EncodedFrame::~EncodedFrame() {

}


/**
 * You pass the control over the data ptr to this class and it will clean up.
 */
VideoFrame::VideoFrame(unsigned int width, unsigned int height, unsigned long timestamp,
		std::vector<unsigned char> &&_data) :
		_width(width), _height(height), _timestamp(timestamp), _data(_data) {
	if (_data.size() != _width * _height * 3) {
		throw std::invalid_argument("Size of data vector is wrong !");
	}
}
;

/**
 * YOu pass the control over the data ptr to this class and it will clean up.
 */
VideoFrame::VideoFrame(unsigned int width, unsigned int height, unsigned long timestamp) :
		_width(width), _height(height), _timestamp(timestamp), _data(
				width * height * 3) {
}
;
/**
 * dtor.
 */
VideoFrame::~VideoFrame() {
}


VideoStream::~VideoStream() {
}
