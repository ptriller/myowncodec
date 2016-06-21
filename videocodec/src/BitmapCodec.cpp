//
// Created by ptriller on 20.06.16.
//

#include "FrameCodec.h"
#include "PmfDecoder.h"
#include "PmfEncoder.h"
#include "netutil.h"



namespace {

    class BitmapDecoder: public FrameDecoder {
    public:
        BitmapDecoder() {};
        virtual ~BitmapDecoder() {};
        virtual std::unique_ptr<VideoFrame> decodeFrame(const EncodedFrame &frame) override {
            auto it = frame.data().begin();
            std::uint32_t width = read_iterator<std::uint32_t>(it);
            std::uint32_t height = read_iterator<std::uint32_t>(it);
            if(width*height*3 + 2*sizeof(std::uint32_t) != frame.data().size()) {
                throw 1;
            }
            std::unique_ptr<VideoFrame> result(new VideoFrame(width, height, frame.timestamp()));
            std::copy(it, frame.data().end(), result->data().begin());
            return result;
        }
    };

    class BitmapEncoder: public FrameEncoder {
    public:
        BitmapEncoder() {}
        virtual ~BitmapEncoder() {}

        virtual std::unique_ptr<EncodedFrame> encodeFrame(const VideoFrame &frame) override {
            std::vector<std::uint8_t> data(frame.data().size() + 2*sizeof(std::uint32_t));
            if(frame.data().size() + 2*sizeof(std::uint32_t) != data.size()) {
                throw 1;
            }
            auto it = data.begin();
            write_iterator(it, frame.width());
            write_iterator(it, frame.height());
            std::copy(frame.data().begin(),frame.data().end(), it);
            return std::unique_ptr<EncodedFrame>(new EncodedFrame(1, frame.timestamp(), std::move(data)));
        }
    };


}
void register_bitmap_codec() {
    PmfDecoder::registerDecoder("bitmap", []() { return new BitmapDecoder(); });
    PmfEncoder::registerEncoder("bitmap", []() { return new BitmapEncoder(); });
}
