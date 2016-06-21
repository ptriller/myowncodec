//
// Created by ptriller on 09.06.16.
//

#ifndef MYOWNCODEC_PMFENCODER_H
#define MYOWNCODEC_PMFENCODER_H

#include "PmfWriter.h"
#include "FrameCodec.h"
#include <functional>
#include <cstdint>
#include <memory>
#include <string>


class PmfEncoder {
public:
    PmfEncoder(const std::string &type, const std::string &filename = "");

    virtual ~PmfEncoder();

    virtual void Open();

    virtual void Open(const std::string &filename);

    void Close();

    void nextFrame(const VideoFrame &);

    static void registerEncoder(const std::string &type, const std::function<FrameEncoder *()> &function);
private:
    PmfWriter writer;
    std::unique_ptr<FrameEncoder> encoder;
};


#endif //MYOWNCODEC_PMFENCODER_H
