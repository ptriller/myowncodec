//
// Created by ptriller on 26.06.2016.
//

#ifndef MYOWNCODEC_PMF_H
#define MYOWNCODEC_PMF_H

#include "codecapi.h"
#include <cstdint>
#include <string>
#include <fstream>
#include <vector>

namespace codec {
    namespace pmf {
        constexpr const char MAGIC[] = {'P', 'M', 'F', 'D', 'A', 'T', 'A'};
        constexpr size_t MAGIC_LEN = sizeof(MAGIC) / sizeof(MAGIC[0]);
        constexpr std::uint8_t VERSION_MAJOR = 1;
        constexpr std::uint8_t VERSION_MINOR = 0;
        constexpr std::uint64_t MAGIC_FRAME = 0xc5823fc96c68f9ab;
    }
    class PmfReader {
    public:
        PmfReader(const std::string &filename);

        PmfReader();

        virtual ~PmfReader();

        void Open(const std::string &filename);

        void Open();

        void Close();

        const std::string type() const { return _type; };

        const std::vector<std::uint8_t> &metadata() const { return _metadata; };

        std::unique_ptr<EncodedFrame> nextFrame();

    private:
        std::ifstream filestream;
        const std::string filename;
        std::string _type;
        std::vector<std::uint8_t> _metadata;
    };


    class PmfWriter {

    public:
        PmfWriter(const std::string &type, const std::string &file = "");

        void Open() { Open(filename); };

        void Open(const std::string &fname);

        void Close();

        void WriteFrame(const EncodedFrame &);

        virtual ~PmfWriter();

    private:
        std::fstream filestream;
        const std::string type;
        const std::string filename;
    };
}

#endif //MYOWNCODEC_PMF_H
