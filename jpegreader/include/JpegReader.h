/*
 * JpegReader.h
 *
 *  Created on: 19.05.2016
 *      Author: ptriller
 */

#ifndef JPEGREADER_SRC_JPEGREADER_H_
#define JPEGREADER_SRC_JPEGREADER_H_
#include "InputFrame.h"
#include <string>

class JpegReader {
public:
	JpegReader() {}
	virtual ~JpegReader();

	InputFrame *createFrame(const std::wstring &filename, unsigned long timestamp);

};

#endif /* JPEGREADER_SRC_JPEGREADER_H_ */
