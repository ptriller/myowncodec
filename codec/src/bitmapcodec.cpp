//
// Created by ptriller on 27.06.16.
//
#include "bitmapcodec.h"
#include "pmf.h"
#include "codecapi.h"
#include "netutil.h"
#include <stdexcept>
#include <iostream>
namespace {

    using namespace codec;

    class BitmapDecoder: public FrameDecoder {
    public:
        BitmapDecoder() {};
        virtual ~BitmapDecoder() {};
        virtual std::unique_ptr<VideoFrame> decodeFrame(const EncodedFrame &frame) override {
            auto it = frame.data().begin();
            std::uint32_t width = read_iterator<std::uint32_t>(it);
            std::uint32_t height = read_iterator<std::uint32_t>(it);
            std::cerr << "Width: " << width << " Height: " << height << std::endl;
            if(width*height*3 + 2*sizeof(std::uint32_t) != frame.data().size()) {
                throw std::runtime_error("Input Bitmap wrong");
            }
            std::unique_ptr<RGBImage> image(new RGBImage(width, height));
            for (auto i = it; i != frame.data().end();++i) {
                if(*i != 0) {
                    std::cerr << "HOSSA" << std::endl;
                    break;
                }
            }
            std::copy(it, frame.data().end(), image->data().begin());
            return std::unique_ptr<VideoFrame>(new VideoFrame(frame.timestamp(), std::move(image)));
        }
    };

    class BitmapEncoder: public FrameEncoder {
    public:
        BitmapEncoder() {}
        virtual ~BitmapEncoder() {}

        virtual std::unique_ptr<EncodedFrame> encodeFrame(const VideoFrame &frame) override {
            const RGBImage &image = frame.image();
            std::vector<std::uint8_t> data(image.data().size() + 2*sizeof(std::uint32_t));
            auto it = data.begin();
            write_iterator(it, image.width());
            write_iterator(it, image.height());
            std::copy(image.data().begin(),image.data().end(), it);
            return std::unique_ptr<EncodedFrame>(new EncodedFrame(1, frame.timestamp(), std::move(data)));
        }
    };


}
void register_bitmap_codec() {
    PmfDecoder::registerDecoder("bitmap", []() { return new BitmapDecoder(); });
    PmfEncoder::registerEncoder("bitmap", []() { return new BitmapEncoder(); });
}
