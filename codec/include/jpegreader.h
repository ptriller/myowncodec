//
// Created by ptriller on 26.06.2016.
//

#ifndef MYOWNCODEC_JPEGREADER_H_H
#define MYOWNCODEC_JPEGREADER_H_H

#include "codecapi.h"
#include <memory>
#include <map>
#include <stdexcept>

namespace codec {

    class JpegVideoSource : public VideoStream {
    public:
        JpegVideoSource(const std::string &directory);

        virtual ~JpegVideoSource();

        virtual void Close();

        virtual std::unique_ptr<VideoFrame> nextFrame();

    private:
        std::uint64_t timestamp;
        std::map<std::uint64_t, std::string> files;
        std::map<std::uint64_t, std::string>::const_iterator iterator;
    };

    class JpegError : public std::runtime_error {
    public:
        JpegError(const std::string &msg) : std::runtime_error(msg) { }

        virtual ~JpegError() { }

    };
    std::unique_ptr<RGBImage> read_jpeg(const std::string &filename);
}

#endif //MYOWNCODEC_JPEGREADER_H_H
