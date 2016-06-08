//
// Created by ptriller on 07.06.16.
//

#ifndef MYOWNCODEC_NETUTIL_H
#define MYOWNCODEC_NETUTIL_H

#include <cstdint>
#include <fstream>


template <typename T>
void write_stream(std::streambuf &out, T value) {
    for(int i = 0; i < sizeof(T); ++i) {
        out.sputc((unsigned char) (value & 0x00FF));
        value >>= 8;
    }
}

template <typename T>
T read_stream(std::streambuf &in) {
    T result = 0;
    for(int i = 0; i < sizeof(T); ++i) {
        result |= static_cast<std::int16_t >(in.sgetc()) << i*8;
    }
    return result;
};

#endif //MYOWNCODEC_NETUTIL_H
