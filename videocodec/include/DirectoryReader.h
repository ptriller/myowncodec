/*
 * DirectoryReader.h
 *
 *  Created on: 22.05.2016
 *      Author: ptriller
 */

#ifndef JPEGREADER_SRC_DIRECTORYREADER_H_
#define JPEGREADER_SRC_DIRECTORYREADER_H_

#include "VideoStream.h"
#include <string>
#include <map>
#include <cstdint>

class DirectoryReader : public VideoStream {
public:
    DirectoryReader(const std::string &directory);

    virtual ~DirectoryReader();

    virtual void Close();

    virtual std::unique_ptr<VideoFrame> nextFrame();

private:
    std::uint64_t timestamp;
    std::map<std::uint64_t, std::string> files;
    std::map<std::uint64_t, std::string>::const_iterator iterator;
};

#endif /* JPEGREADER_SRC_DIRECTORYREADER_H_ */
