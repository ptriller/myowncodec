//
// Created by ptriller on 08.06.16.
//

#include "PmfWriter.h"
#include "DirectoryReader.h"
#include "VideoFrame.h"
#include "EncodedFrame.h"
#include <iostream>

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <directory> <outputfile>" << std::endl;
        return 1;
    }
    DirectoryReader reader(argv[1]);
    PmfWriter writer;
    writer.Open(argv[2]);
    for (std::unique_ptr<VideoFrame> frame(reader.nextFrame()); frame; frame = reader.nextFrame()) {
        std::cerr << frame->timestamp() << std::endl;
        std::vector<unsigned char> buf(frame->width()*frame->height()+2* sizeof(std::uint32_t));
        std::co
        EncodedFrame outputFrame(1,frame->timestamp(),
                                 std::vector<unsigned char>(frame->buffer(0,0),
        frame->buffer(0,0)+frame->width()*frame->height()));
        writer.WriteFrame(outputFrame);
    }
    writer.Close();
    reader.Close();
    return 0;
}