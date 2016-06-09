//
// Created by ptriller on 09.06.16.
//

#ifndef MYOWNCODEC_PMF_H
#define MYOWNCODEC_PMF_H
#include <string>
#include <cstdint>

namespace pmf {
    constexpr const char MAGIC[] = { 'P', 'M', 'F', 'D', 'A', 'T', 'A' };
    constexpr size_t MAGIC_LEN = sizeof(MAGIC)/sizeof(MAGIC[0]);
    constexpr std::uint8_t VERSION_MAJOR = 1;
    constexpr std::uint8_t VERSION_MINOR = 0;
    constexpr std::uint64_t MAGIC_FRAME = 0xc5823fc96c68f9ab;
}

#endif //MYOWNCODEC_PMF_H
