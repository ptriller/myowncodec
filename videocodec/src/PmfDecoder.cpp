//
// Created by ptriller on 09.06.16.
//

#include "PmfDecoder.h"
#include "EncodedFrame.h"
#include "VideoFrame.h"
#include "netutil.h"
#include <unordered_map>

namespace {
    std::unordered_map<std::string, std::function<FrameDecoder *()>> decoderMap;
}


PmfDecoder::PmfDecoder() { }

PmfDecoder::PmfDecoder(const std::string &filename) : reader(filename) { }

PmfDecoder::~PmfDecoder() { }

void PmfDecoder::Open() {
    reader.Open();

}

void PmfDecoder::Open(const std::string &filename) {
    reader.Open(filename);
}

void PmfDecoder::Close() {
    reader.Close();
}

std::unique_ptr<VideoFrame> PmfDecoder::nextFrame() {
    std::unique_ptr<EncodedFrame> frame = reader.nextFrame();
    if (frame) {
        auto it = frame->data().begin();
        std::uint32_t width = read_iterator<std::uint32_t>(it);
        std::uint32_t height = read_iterator<std::uint32_t>(it);
        return std::unique_ptr<VideoFrame>(new VideoFrame(width,
                                                          height,
                                                          frame->timestamp(),
                                                          std::vector<std::uint8_t>(it, frame->data().end())));
    }
    return std::unique_ptr<VideoFrame>();
}



void PmfDecoder::registerDecoder(const std::string &type, const std::function<FrameDecoder *()> &function) {
    decoderMap.insert(std::make_pair(type, function));
}