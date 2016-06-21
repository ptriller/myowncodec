//
// Created by ptriller on 20.06.16.
//

#ifndef MYOWNCODEC_FRAMEDECODER_H
#define MYOWNCODEC_FRAMEDECODER_H

#include "EncodedFrame.h"
#include "VideoFrame.h"
#include <memory>


class FrameDecoder {
public:
    virtual ~FrameDecoder() {}
    virtual std::unique_ptr<VideoFrame> decodeFrame(const EncodedFrame &) = 0;

};

class FrameEncoder {
public:
    virtual ~FrameEncoder() {}
    virtual std::unique_ptr<EncodedFrame> encodeFrame(const VideoFrame &) = 0;
};

#endif //MYOWNCODEC_FRAMEDECODER_H
