//
// Created by ptriller on 07.06.16.
//

#include "PmfReader.h"


PmfReader::PmfReader() {}

PmfReader::PmfReader(const std::string &filename): filename(filename) {

}

void PmfReader::Open() {
    Open(filename);
}

void PmfReader::Open(const std::string &filename) {
    filestream.open(filename, std::ios::binary | std::ios::in);

}


void PmfReader::Close() {
    filestream.close();
}