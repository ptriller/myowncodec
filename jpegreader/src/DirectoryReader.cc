/*
 * DirectoryReader.cc
 *
 *  Created on: 22.05.2016
 *      Author: ptriller
 */

#include "DirectoryReader.h"
#include "JpegReader.h"
#include "dirent.h"
#include <stdexcept>
#include <regex>
#include <iostream>
#include <map>
#include <sstream>

namespace {
    std::regex filename_pattern("frame([0-9]+)\\.jpg");

    struct Directory {
        DIR *dir;

        Directory(const std::string &directory) {
            dir = ::opendir(directory.c_str());
        }

        ~Directory() {
            if (dir != NULL) {
                ::closedir(dir);
            }
        }

        operator DIR *() {
            return dir;
        }
    };

    JpegReader reader;
}

DirectoryReader::DirectoryReader(const std::string &directory) :
        timestamp(0l) {
    Directory dir(directory);
    struct dirent *dp;
    if (dir == NULL) {
        throw std::invalid_argument("Unable to read Directory");
    }
    std::cmatch base_match;
    while ((dp = ::readdir(dir)) != NULL) {
        if (std::regex_match(dp->d_name, base_match, filename_pattern)) {
            std::stringstream filename;
            filename << directory;
            if (directory.back() != '/' && directory.back() != '\\') filename << '/';
            filename << dp->d_name;
            std::cerr << filename.str() << std::endl;
            files[std::stoul(base_match[1].str())] = std::string(filename.str());
        }
    }
    iterator = files.begin();
}

DirectoryReader::~DirectoryReader() {
}

void DirectoryReader::close() {
    iterator = files.end();
}

VideoFrame *DirectoryReader::nextFrame() {
    if (iterator != files.end()) {
        VideoFrame *frame = reader.createFrame(iterator->second, iterator->first * 50);
        ++iterator;
        return frame;
    }
    return NULL;
}
