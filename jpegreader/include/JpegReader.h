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
#include <stdexcept>

class JpegReader {
public:
    JpegReader() { }

    virtual ~JpegReader();

    VideoFrame *createFrame(const std::string &filename, std::uint64_t timestamp);

};

class JpegError : public std::runtime_error {
public:
    JpegError(const std::string &msg) : std::runtime_error(msg) { }

    virtual ~JpegError() { }

};

#endif /* JPEGREADER_SRC_JPEGREADER_H_ */
