//
// Created by ptriller on 23.06.16.
//

#ifndef MYOWNCODEC_YCCCONVERTER_H
#define MYOWNCODEC_YCCCONVERTER_H

#include "VideoFrame.h"
#include "ComponentImage.h"
#include <memory>

std::unique_ptr<ComponentImage> frame_to_ycc(const VideoFrame &);



#endif //MYOWNCODEC_YCCCONVERTER_H
