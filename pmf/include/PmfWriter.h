//
// Created by ptriller on 06.06.16.
//

#ifndef MYOWNCODEC_PMFWRITER_H
#define MYOWNCODEC_PMFWRITER_H

#include <string>
#include <fstream>
#include <string>

class EncodedFrame;

class PmfWriter {

public:
    PmfWriter();
    PmfWriter(const std::string &file);

    void Open() { Open(filename); };

    void Open(const std::string &fname);

    void Close();

    void WriteFrame(const EncodedFrame &);

    virtual ~PmfWriter();

private:
    std::filebuf filestream;
    const std::string filename;
};


#endif //MYOWNCODEC_PMFWRITER_H
