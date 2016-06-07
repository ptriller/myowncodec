//
// Created by ptriller on 06.06.16.
//

#include "PmfWriter.h"
#include "EncodedFrame.h"
#include "netutil.h"
#include <iterator>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <functional>

namespace {
    std::string MAGIC("PMFDATA");
    uint8_t VERSION_MAJOR = 1;
    uint8_t VERSION_MINOR = 0;
    uint64_t MAGIC_FRAME = 0xc5823fc96c68f9ab;
}

PmfWriter::PmfWriter() {
}

PmfWriter::PmfWriter(const std::string &file): filename(file) {
}


void PmfWriter::Open(const std::string &fname) {
    filestream.open(fname, std::ios::out);
    if(!filestream.is_open()) {
        throw 1;
    }
    //Write Magic Header
    std::for_each(MAGIC.begin(), MAGIC.end(),std::bind(&std::streambuf::sputc, &filestream, std::placeholders::_1));
//    std::for_each(MAGIC.begin(), MAGIC.end(),[this](const char c) { filestream.sputc(c); });
    //Write Version Bytes.
    filestream.sputc(VERSION_MAJOR);
    filestream.sputc(VERSION_MINOR);
    // Metadata Block size... 0 for now
    write_stream(filestream, (std::uint32_t)0);
}


void PmfWriter::Close() {
    filestream.close();
}

void PmfWriter::WriteFrame(const EncodedFrame &frame) {
    write_stream(filestream, MAGIC_FRAME);
    write_stream(filestream, frame.timestamp());
    write_stream(filestream, frame.frameType());
    write_stream(filestream, (std::uint32_t) frame.data().size());
    std::for_each(frame.data().begin(), frame.data().end(),[this](auto c) { filestream.sputc(c); });
}
PmfWriter::~PmfWriter() {
    Close();
}


