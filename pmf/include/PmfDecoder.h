//
// Created by ptriller on 09.06.16.
//

#ifndef MYOWNCODEC_PMFDECODER_H
#define MYOWNCODEC_PMFDECODER_H

#include "VideoStream.h"
#include "PmfReader.h"
#include <functional>
#include <cstdint>

class PmfDecoder: public VideoStream {
public:
    PmfDecoder();

    PmfDecoder(const std::string &filename);

    virtual ~PmfDecoder();

    virtual void Open();

    virtual void Open(const std::string &filename);

    void Close() override;

    std::unique_ptr<VideoFrame> nextFrame() override;

    static void registerDecoder(std::uint32_t frameType, const std::function<VideoFrame *(EncodedFrame *)> &function);
private:
    PmfReader reader;
};


#endif //MYOWNCODEC_PMFDECODER_H
