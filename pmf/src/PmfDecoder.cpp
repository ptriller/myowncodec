//
// Created by ptriller on 09.06.16.
//

#include "PmfDecoder.h"
#include "EncodedFrame.h"
#include "VideoFrame.h"

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
    return std::unique_ptr<VideoFrame>(new VideoFrame(frame->));
}