//
// Created by ptriller on 07.06.16.
//

#ifndef MYOWNCODEC_NETUTIL_H
#define MYOWNCODEC_NETUTIL_H

#include <cstdint>
#include <fstream>

inline void write_stream(std::streambuf &out, std::uint64_t value) {
    for(int i = 0; i < 8; ++i) {
        out.sputc((unsigned char)(value & 0x00000000000000FF));
        value >>= 8;
    }
}

inline void write_stream(std::streambuf &out, std::uint32_t value) {
    for(int i = 0; i < 4; ++i) {
        out.sputc((unsigned char)(value & 0x000000FF));
        value >>= 8;
    }
}

inline void write_stream(std::streambuf &out, std::uint16_t value) {
    for(int i = 0; i < 2; ++i) {
        out.sputc((unsigned char)(value & 0x00FF));
        value >>= 8;
    }
}


inline void write_stream(std::streambuf &out, std::int64_t value) {
    for(int i = 0; i < 8; ++i) {
        out.sputc((unsigned char)(value & 0x00000000000000FF));
        value >>= 8;
    }
}

inline void write_stream(std::streambuf &out, std::int32_t value) {
    for(int i = 0; i < 4; ++i) {
        out.sputc((unsigned char)(value & 0x000000FF));
        value >>= 8;
    }
}

inline void write_stream(std::streambuf &out, std::int16_t value) {
    for(int i = 0; i < 2; ++i) {
        out.sputc((unsigned char)(value & 0x00FF));
        value >>= 8;
    }
}

#endif //MYOWNCODEC_NETUTIL_H
