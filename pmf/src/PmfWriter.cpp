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
    std::uint8_t VERSION_MAJOR = 1;
    std::uint8_t VERSION_MINOR = 0;
    std::uint64_t MAGIC_FRAME = 0xc5823fc96c68f9ab;
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
    for(char c: MAGIC) filestream.sputc(c);
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
    for(unsigned char c: frame.data()) filestream.sputc(c);
}
PmfWriter::~PmfWriter() {
    Close();
}


