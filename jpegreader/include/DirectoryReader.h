/*
 * DirectoryReader.h
 *
 *  Created on: 22.05.2016
 *      Author: ptriller
 */

#ifndef DIRECTORYREADER_H_
#define DIRECTORYREADER_H_

#include <VideoStream.h>
#include <string>

class DirectoryReader: public VideoStream {
public:
	DirectoryReader(const std::string &directory);

	virtual ~DirectoryReader();

	virtual void close();

	virtual std::unique_ptr<VideoFrame> nextFrame();
};

#endif /* DIRECTORYREADER_H_ */
