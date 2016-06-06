//
// Created by ptriller on 06.06.16.
//

#include "PmfWriter.h"


PmfWriter::PmfWriter() {
}

PmfWriter::PmfWriter(const std::string &file): filename(file) {
}


void PmfWriter::Open() {
    filestream.open(filename, std::ios::trunc | std::ios::out | std::ios::binary);
    if(filestream.bad()) {
        throw 1;
    }
}

PmfWriter::~PmfWriter() {

}


