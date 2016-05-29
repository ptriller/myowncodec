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
#include <map>

class DirectoryReader: public VideoStream {
public:
	DirectoryReader(const std::string &directory);

	virtual ~DirectoryReader();

	virtual void close();

	virtual VideoFrame *nextFrame();
private:
	unsigned long timestamp;
	std::map<unsigned long, std::string> files;
	std::map<unsigned long, std::string>::const_iterator iterator;
};

#endif /* JPEGREADER_SRC_DIRECTORYREADER_H_ */
