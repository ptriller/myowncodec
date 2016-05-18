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
	typedef const unsigned char img_data[];

	InputFrame()
	/**
	 * dtor.
	 */
	virtual ~InputFrame() {}
	/**
	 * Timestamp of the Frame in nanoseconds. SHOULD be 0 based
	 * within a movie.
	 */
	virtual unsigned long timestamp() const = 0;
	/**
	 * width of the Frame. MUST be constant within a movie.
	 */
	virtual unsigned int width() const = 0;
	/**
	 * height of the Frame. MUST be constant within a movie.
	 */
	virtual unsigned int height() const = 0;
	/**
	 * Access the bitplane Data.
	 * red has an index of 0, green 1 and blue 2.
	 */
	virtual const img_data& operator [](unsigned int idx) const = 0;

private:
	const unsigned char &data[3][];

};
#endif /* INPUTFRAME_H_ */
