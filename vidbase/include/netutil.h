//
// Created by ptriller on 07.06.16.
//

#ifndef MYOWNCODEC_NETUTIL_H
#define MYOWNCODEC_NETUTIL_H

#include <cstdint>
#include <fstream>


template <typename T, typename U>
void write_stream(std::basic_ostream<U> &out, T value) {
    for(int i = 0; i < sizeof(T); ++i) {
        out.put((unsigned char) (value & 0x00FF));
        value >>= 8;
    }
}

template <typename T, typename U>
T read_stream(std::basic_istream<U> &in) {
    T result = 0;
    for(int i = 0; i < sizeof(T); ++i) {
        result |= static_cast<T>(in.get()) << i*8;
    }
    return result;
};

#endif //MYOWNCODEC_NETUTIL_H
