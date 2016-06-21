//
// Created by ptriller on 08.06.16.
//

#include "PmfEncoder.h"
#include "DirectoryReader.h"
#include "codecs.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    register_bitmap_codec();
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <type> <directory> <outputfile>" << std::endl;
        return 1;
    }
    DirectoryReader reader(argv[2]);
    PmfEncoder encoder(argv[1]);
    encoder.Open(argv[3]);
    for (std::unique_ptr<VideoFrame> frame(reader.nextFrame()); frame; frame = reader.nextFrame()) {
        std::cerr << frame->timestamp() << std::endl;
        encoder.nextFrame(*frame);
    }
    encoder.Close();
    reader.Close();
    return 0;
}