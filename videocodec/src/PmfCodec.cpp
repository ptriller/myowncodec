//
// Created by ptriller on 09.06.16.
//

#include "PmfDecoder.h"
#include "EncodedFrame.h"
#include "VideoFrame.h"
#include "netutil.h"
#include <unordered_map>
#include "PmfEncoder.h"

namespace {
    std::unordered_map<std::string, std::function<FrameDecoder *()>> decoderMap;
    std::unordered_map<std::string, std::function<FrameEncoder *()>> encoderMap;
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



PmfEncoder::PmfEncoder(const std::string &type, const std::string &filename): writer(type, filename) {
    auto factoryIt = encoderMap.find(type);
    if(factoryIt == encoderMap.end()) throw 1;
    encoder.reset(factoryIt->second());
}

PmfEncoder::~PmfEncoder() { }

void PmfEncoder::Open() {
    writer.Open();
}


void PmfEncoder::Open(const std::string &filename) {
    writer.Open(filename);
}


void PmfEncoder::Close() {
    writer.Close();
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