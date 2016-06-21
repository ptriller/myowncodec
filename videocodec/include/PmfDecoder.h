//
// Created by ptriller on 09.06.16.
//

#ifndef MYOWNCODEC_PMFDECODER_H
#define MYOWNCODEC_PMFDECODER_H

#include "VideoStream.h"
#include "PmfReader.h"
#include "FrameCodec.h"
#include <functional>
#include <cstdint>
#include <memory>
#include <string>


class PmfDecoder: public VideoStream {
public:
    PmfDecoder();

    PmfDecoder(const std::string &filename);

    virtual ~PmfDecoder();

    virtual void Open();

    virtual void Open(const std::string &filename);

    void Close() override;

    std::unique_ptr<VideoFrame> nextFrame() override;

    static void registerDecoder(const std::string &type, const std::function<FrameDecoder *()> &function);
private:
    PmfReader reader;
    std::unique_ptr<FrameDecoder *> decoder;
};


#endif //MYOWNCODEC_PMFDECODER_H
