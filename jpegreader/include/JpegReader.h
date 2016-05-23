/*
 * JpegReader.h
 *
 *  Created on: 19.05.2016
 *      Author: ptriller
 */

#ifndef JPEGREADER_SRC_JPEGREADER_H_
#define JPEGREADER_SRC_JPEGREADER_H_
#include <VideoFrame.h>
#include <string>
#include <memory>

class JpegReader {
public:
	JpegReader() {}
	virtual ~JpegReader();

	std::unique_ptr<VideoFrame> createFrame(const std::string &filename, unsigned long timestamp);

};

#endif /* JPEGREADER_SRC_JPEGREADER_H_ */
