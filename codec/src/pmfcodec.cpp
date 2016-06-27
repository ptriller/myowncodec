//
// Created by ptriller on 27.06.16.
//

#include "pmf.h"
#include "netutil.h"
#include <unordered_map>

namespace {
    std::unordered_map<std::string, std::function<codec::FrameDecoder *()>> decoderMap;
    std::unordered_map<std::string, std::function<codec::FrameEncoder *()>> encoderMap;
}


namespace codec {

    PmfDecoder::PmfDecoder(const std::string &filename) :reader(filename) {
    }

    void PmfDecoder::initialize() {
        auto factoryIt = decoderMap.find(reader.type());
        if(factoryIt == decoderMap.end()) throw 1;
        decoder.reset(factoryIt->second());
    }

    std::unique_ptr<VideoFrame> PmfDecoder::nextFrame() {
        std::unique_ptr<EncodedFrame> frame = reader.nextFrame();
        if (frame) {
            auto it = frame->data().begin();
            std::uint32_t width = read_iterator<std::uint32_t>(it);
            std::uint32_t height = read_iterator<std::uint32_t>(it);
            std::unique_ptr<RGBImage> image(new RGBImage(width, height));
            std::copy(it, frame->data().end(), image->data().begin());
            return std::unique_ptr<VideoFrame>(new VideoFrame(frame->timestamp(),std::move(image)));
        }
        return std::unique_ptr<VideoFrame>();
    }

    PmfEncoder::PmfEncoder(const std::string &type, const std::string &filename): writer(type, filename) {
        auto factoryIt = encoderMap.find(type);
        if(factoryIt == encoderMap.end()) throw 1;
        encoder.reset(factoryIt->second());
    }

    void PmfEncoder::nextFrame(const VideoFrame &frame) {
        writer.WriteFrame(*encoder->encodeFrame(frame));
    }

    void PmfDecoder::registerDecoder(const std::string &type, const std::function<FrameDecoder *()> &function) {
        decoderMap.insert(std::make_pair(type, function));
    }

    void PmfEncoder::registerEncoder(const std::string &type, const std::function<FrameEncoder *()> &function) {
        encoderMap.insert(std::make_pair(type, function));
    }
}

