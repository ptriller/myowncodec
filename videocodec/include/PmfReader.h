//
// Created by ptriller on 07.06.16.
//

#ifndef MYOWNCODEC_PMFREADER_H
#define MYOWNCODEC_PMFREADER_H
#include "VideoStream.h"
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <cstdint>
class EncodedFrame;

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


#endif //MYOWNCODEC_PMFREADER_H
