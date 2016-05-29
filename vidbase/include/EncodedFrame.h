/*
 * EncodedFrame.h
 *
 *  Created on: 27.05.2016
 *      Author: ptriller
 */

#ifndef INCLUDE_ENCODEDFRAME_H_
#define INCLUDE_ENCODEDFRAME_H_
#include<vector>

class EncodedFrame {
public:
	EncodedFrame(unsigned int frameType, unsigned long timestamp,
			std::vector<unsigned char> &&data);
	virtual ~EncodedFrame();
	const unsigned int frameType() const { return _frameType; }
	const unsigned long timestamp() const { return _timestamp; }
	const std::vector<unsigned char> &data() const { return _data; }
private:
	unsigned int _frameType;
	unsigned long _timestamp;
	std::vector<unsigned char> _data;
};

#endif /* INCLUDE_ENCODEDFRAME_H_ */
