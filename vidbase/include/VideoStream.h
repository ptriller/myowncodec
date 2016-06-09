/*
 * InputStream.h
 *
 *  Created on: 16.05.2016
 *      Author: ptriller
 */

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include <memory>
class VideoFrame;

class VideoStream {
public:
    virtual ~VideoStream();

    virtual void Close() = 0;

    virtual std::unique_ptr<VideoFrame> nextFrame() = 0;

};


#endif /* VIDEOSTREAM_H_ */
