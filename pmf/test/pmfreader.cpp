//
// Created by ptriller on 09.06.16.
//
#include "PmfReader.h"
#include "EncodedFrame.h"
#include <iostream>
int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    }
    PmfReader reader(argv[1]);
    reader.Open();
    ;
    for(std::unique_ptr<EncodedFrame> frame(reader.nextFrame().release()); frame; frame.reset(reader.nextFrame().release())) {
        std::cout << "Frame:" << frame->timestamp() << std::endl;
    }
}