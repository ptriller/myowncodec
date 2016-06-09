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

#include "pmf.h"


using namespace pmf;

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
    for(char c: MAGIC) filestream.put(c);
    //Write Version Bytes.
    filestream.put(VERSION_MAJOR);
    filestream.put(VERSION_MINOR);
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
    for(unsigned char c: frame.data()) filestream.put(c);
}

PmfWriter::~PmfWriter() {
    Close();
}


