/*
 * DirectoryReader.h
 *
 *  Created on: 22.05.2016
 *      Author: ptriller
 */

#ifndef JPEGREADER_SRC_DIRECTORYREADER_H_
#define JPEGREADER_SRC_DIRECTORYREADER_H_

#include <VideoStream.h>
#include <string>

class DirectoryReader: public VideoStream {
public:
	DirectoryReader(const std::string &directory);

	virtual ~DirectoryReader();

	virtual void close();

	virtual VideoFrame *nextFrame();
};

#endif /* JPEGREADER_SRC_DIRECTORYREADER_H_ */
