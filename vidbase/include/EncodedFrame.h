/*
 * EncodedFrame.h
 *
 *  Created on: 27.05.2016
 *      Author: ptriller
 */

#ifndef INCLUDE_ENCODEDFRAME_H_
#define INCLUDE_ENCODEDFRAME_H_

#include<vector>
#include <cstdint>
#include <cstdint>
class EncodedFrame {
public:
    EncodedFrame(std::uint32_t frameType, std::uint64_t timestamp,
                 std::vector<unsigned char> &&data);

    virtual ~EncodedFrame();

    const std::uint32_t frameType() const { return _frameType; }

    const std::uint64_t timestamp() const { return _timestamp; }

    const std::vector<unsigned char> &data() const { return _data; }

private:
    std::uint32_t _frameType;
    std::uint64_t _timestamp;
    std::vector<unsigned char> _data;
};

#endif /* INCLUDE_ENCODEDFRAME_H_ */
