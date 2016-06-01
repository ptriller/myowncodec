#include "DirectoryReader.h"
#include "VideoFrame.h"
#include <iostream>
#include <memory>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory>" << std::endl;
        return 1;
    }
    DirectoryReader reader(argv[1]);
    for (std::unique_ptr<VideoFrame> frame(reader.nextFrame()); frame; frame.reset(reader.nextFrame())) {
        std::cerr << frame->timestamp() << std::endl;
    }
}
