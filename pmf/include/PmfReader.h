//
// Created by ptriller on 07.06.16.
//

#ifndef MYOWNCODEC_PMFREADER_H
#define MYOWNCODEC_PMFREADER_H
#include "VideoStream.h"
#include <fstream>

class PmfReader {
public:
    PmfReader(const std::string &filename);
    PmfReader();

    virtual ~PmfReader();
    void Open(const std::string &filename);
    void Open();
    void Close();

    EncodedFrame
private:
    std::ifstream filestream;
    const std::string filename;
};


#endif //MYOWNCODEC_PMFREADER_H
