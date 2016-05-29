/*
 * InputFrame.h
 *
 *  Created on: 15.05.2016
 *      Author: ptriller
 */

#ifndef INPUTFRAME_H_
#define INPUTFRAME_H_
#include <stdexcept>
#include <vector>

/**
 * Input Frame for the Encode. The format is RGB with 8-bit per color.
 * 0,0 is top left.
 */

class VideoFrame {

public:

	/**
	 * You pass the control over the data ptr to this class and it will clean up.
	 */
	VideoFrame(unsigned int width, unsigned int height, unsigned long timestamp,
			std::vector<unsigned char> &&_data);

	/**
	 * YOu pass the control over the data ptr to this class and it will clean up.
	 */
	VideoFrame(unsigned int width, unsigned int height, unsigned long timestamp);

	/**
	 * dtor.
	 */
	virtual ~VideoFrame();
	/**
	 * Timestamp of the Frame in nanoseconds. SHOULD be 0 based
	 * within a movie.
	 */
	inline unsigned long timestamp() const {
		return _timestamp;
	}
	;
	/**
	 * width of the Frame. MUST be constant within a movie.
	 */
	inline unsigned int width() const {
		return _width;
	}
	/**
	 * height of the Frame. MUST be constant within a movie.
	 */
	inline unsigned int height() const {
		return _height;
	}

	/**
	 * get(1,1)[0] = red
	 * get(1,1)[1] = green
	 * get(1,1)[2] = blue
	 */
	inline const unsigned char * get(unsigned int x, unsigned int y) const {
		if (x >= _width || y >= _height) {
			throw std::invalid_argument("coordinates out of bounds");
		}
		return &_data[3 * (y * _width + x)];
	}

	/**
	 * get(1,1)[0] = red
	 * get(1,1)[1] = green
	 * get(1,1)[2] = blue
	 */
	inline unsigned char * buffer(unsigned int x, unsigned int y) {
		if (x >= _width || y >= _height) {
			throw std::invalid_argument("coordinates out of bounds");
		}
		return &_data[3 * (y * _width + x)];
	}

private:
	const unsigned int _width;
	const unsigned int _height;
	const unsigned long _timestamp;
	std::vector<unsigned char> _data;
};
#endif /* INPUTFRAME_H_ */
