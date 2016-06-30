//
// Created by ptriller on 27.06.16.
//
#include "bitmapcodec.h"
#include "jpegreader.h"
#include "pmf.h"
#include <iostream>
#include "ppeg.h"
int main(int argc, const char *argv[]) {
    ppeg::ComponentBitmap bitmap, bitmat2;

    bitmap = std::move(bitmat2);
    register_bitmap_codec();
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <type> <directory> <outputfile>" << std::endl;
        return 1;
    }
    codec::JpegVideoSource source(argv[2]);
    codec::PmfEncoder encoder(argv[1]);
    encoder.Open(argv[3]);
    for (std::unique_ptr<codec::VideoFrame> frame(source.nextFrame()); frame; frame = source.nextFrame()) {
        std::cerr << frame->timestamp() << std::endl;
        encoder.nextFrame(*frame);
    }
    encoder.Close();
    source.Close();
    return 0;
}