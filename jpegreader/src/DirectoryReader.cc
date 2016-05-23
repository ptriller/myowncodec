/*
 * DirectoryReader.cc
 *
 *  Created on: 22.05.2016
 *      Author: ptriller
 */

#include "DirectoryReader.h"
#include "VideoFrame.h"

DirectoryReader::DirectoryReader(const std::string &directory) {
	// TODO Auto-generated constructor stub

}

DirectoryReader::~DirectoryReader() {
	// TODO Auto-generated destructor stub
}

void DirectoryReader::close() {
}

std::unique_ptr<VideoFrame> DirectoryReader::nextFrame() {
	return std::unique_ptr<VideoFrame>(nullptr);
}
