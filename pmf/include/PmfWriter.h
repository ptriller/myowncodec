//
// Created by ptriller on 06.06.16.
//

#ifndef MYOWNCODEC_PMFWRITER_H
#define MYOWNCODEC_PMFWRITER_H

#include <string>
#include <fstream>
#include <string>

class PmfWriter {

public:
    PmfWriter();
    PmfWriter(const std::string &file);

    void Open();

    virtual ~PmfWriter();

private:
    std::ofstream filestream;
    const std::string filename;
};


#endif //MYOWNCODEC_PMFWRITER_H
