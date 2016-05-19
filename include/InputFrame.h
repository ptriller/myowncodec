/*
 * InputFrame.h
 *
 *  Created on: 15.05.2016
 *      Author: ptriller
 */

#ifndef INPUTFRAME_H_
#define INPUTFRAME_H_

/**
 * Input Frame for the Encode. The format is RGB with 8-bit per color.
 * 0,0 is top left.
 */
class InputFrame {

public:

	InputFrame(unsigned int width, unsigned int height,
			   unsigned long timestamp,
			   const unsigned char * const * const data):
			   _width(width),_height(height), _timestamp(timestamp),_data(data) {};
	/**
	 * dtor.
	 */
	virtual ~InputFrame() {}
	/**
	 * Timestamp of the Frame in nanoseconds. SHOULD be 0 based
	 * within a movie.
	 */
	virtual unsigned long timestamp() const { return _timestamp; };
	/**
	 * width of the Frame. MUST be constant within a movie.
	 */
	virtual unsigned int width() const { return _width; }
	/**
	 * height of the Frame. MUST be constant within a movie.
	 */
	virtual unsigned int height() const { return _height; }
	/**
	 * Access the bitplane Data.
	 * red has an index of 0, green 1 and blue 2.
	 */
	const unsigned char * const operator [](unsigned int idx) { return _data[idx]; }

private:
	const unsigned int _width;
	const unsigned int _height;
	const unsigned long _timestamp;
	const unsigned char * const * const _data;

};
#endif /* INPUTFRAME_H_ */
