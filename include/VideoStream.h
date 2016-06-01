/*
 * InputStream.h
 *
 *  Created on: 16.05.2016
 *      Author: ptriller
 */

#ifndef INPUTSTREAM_H_
#define VIDEOSTREAM_H_

#include <memory>

class VideoFrame;

class VideoStream {
public:
    virtual ~VideoStream() { }

    virtual void close() = 0;

    virtual std::unique_ptr<VideoFrame> nextFrame() = 0;

};


#endif /* INPUTSTREAM_H_ */
