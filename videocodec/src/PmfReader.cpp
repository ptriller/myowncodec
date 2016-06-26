//
// Created by ptriller on 07.06.16.
//

#include "PmfReader.h"
#include "EncodedFrame.h"
#include "netutil.h"
#include "pmf.h"

#include <iostream>
#include <sstream>
using namespace pmf;

PmfReader::PmfReader() {}

PmfReader::PmfReader(const std::string &filename): filename(filename) {

}

PmfReader::~PmfReader() {
    Close();
}
void PmfReader::Open() {
    Open(filename);
}

void PmfReader::Open(const std::string &filename) {
    filestream.open(filename, std::ios::binary | std::ios::in);
    // Validate Header
    for(size_t i = 0; i < MAGIC_LEN;++i) {
        if(filestream.get() != MAGIC[i]) {
            std::cerr << "Header Wrong at position " << i << std::endl;
            throw 1;
        }
    }
    std::uint8_t majorVersion = (uint8_t) filestream.get();
    std::uint8_t minorVersion = (uint8_t) filestream.get();
    std::cout << "Reading PMF File Version " << (int)majorVersion << '.' << (int)minorVersion << std::endl;
    uint16_t length = read_stream<std::uint16_t>(filestream);
    std::stringstream inputStream;
    for(int i = 0; i < length;++i) inputStream.put((std::stringstream::char_type)filestream.get());
    std::cout << "Format is: "  << inputStream.str() << std::endl;
    std::uint32_t metaDataSize = read_stream<std::uint32_t>(filestream);
    std::cout << "Metadata size " << metaDataSize  << std::endl;
    filestream.ignore(metaDataSize);
}


std::unique_ptr<EncodedFrame> PmfReader::nextFrame() {
    if(filestream.eof()) {
        return std::unique_ptr<EncodedFrame>(nullptr);
    }
    std::uint32_t i= 0;
    for(std::uint64_t magic = read_stream<std::uint64_t>(filestream);magic != pmf::MAGIC_FRAME;
        magic = read_stream<std::uint64_t>(filestream)) {
        if(filestream.eof()) {
            if(i > 0) {
                std::cerr << "Garbage at the end" << std::endl;
            }

            return std::unique_ptr<EncodedFrame>(nullptr);
        }
        ++i;
    }
    if(i > 0) {
        std::cerr << "Skipped " << i << "Bytes to find Magic Number" << std::endl;
    }
    std::uint64_t timestamp = read_stream<std::uint64_t>(filestream);
    std::uint32_t frameType = read_stream<std::uint32_t>(filestream);
    std::uint32_t dataSize = read_stream<std::uint32_t>(filestream);
    std::vector<std::uint8_t> data(dataSize);
    filestream.read((char *) &data[0], data.size());
    return std::unique_ptr<EncodedFrame>(new EncodedFrame(frameType, timestamp, std::move(data)));
}

void PmfReader::Close() {
    filestream.close();
}