//
// Created by ptriller on 26.06.2016.
//
#include <cstdio>
#include <cstdint>
#include "jpeglib.h"
#include "jpegreader.h"
#include <stdexcept>
#include <iostream>
#include <cerrno>
#include <regex>
#include <cstring>
#include <fstream>
#include "dirent.h"


namespace codec {

    std::unique_ptr<RGBImage> read_jpeg(const std::string &filename) {
        struct jpeg_decompress_struct cinfo;
        struct jpeg_error_mgr jerr;

        cinfo.err = jpeg_std_error(&jerr);
        jerr.error_exit = [](j_common_ptr cinfo) { throw cinfo->err; };
        try {
            jpeg_create_decompress(&cinfo);
            FILE *infile = std::fopen(filename.c_str(), "rb");
            if (infile == NULL) {
                std::cerr << "Unable to opein JPEG File: " << std::strerror(errno) << std::endl;
                return NULL;
            }
            // TODO ERROR
            jpeg_stdio_src(&cinfo, infile);
            jpeg_read_header(&cinfo, TRUE);
            jpeg_start_decompress(&cinfo);
            if (cinfo.output_components != 3) {
                throw cinfo.err;
            }
            std::uint32_t width = cinfo.output_width;
            std::uint32_t height = cinfo.output_height;
            std::unique_ptr<RGBImage> image(new RGBImage(width, height));
            while (cinfo.output_scanline < height) {
                unsigned char *buffer_array[1];
                buffer_array[0] = &image->data().at(cinfo.output_scanline * width*3);
                jpeg_read_scanlines(&cinfo, buffer_array, 1);
            }
            jpeg_finish_decompress(&cinfo);
            fclose(infile);
            jpeg_destroy_decompress(&cinfo);
            return image;
        } catch (struct jpeg_error_mgr *err) {
            char pszErr[JMSG_LENGTH_MAX];
            (cinfo.err->format_message)((j_common_ptr) &cinfo, pszErr);
            std::string error(pszErr);
            std::cerr << "Error: " << error << std::endl;
            jpeg_destroy_decompress(&cinfo);
            throw JpegError(error);
        }
    }

}
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
}

namespace codec {
    JpegVideoSource::JpegVideoSource(const std::string &directory) :
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
                files[std::stoul(base_match[1].str())] = std::string(filename.str());
            }
        }
        iterator = files.begin();
    }

    JpegVideoSource::~JpegVideoSource() {
    }

    void JpegVideoSource::Close() {
        iterator = files.end();
    }

    std::unique_ptr<VideoFrame> JpegVideoSource::nextFrame() {
        if (iterator != files.end()) {
            return std::unique_ptr<VideoFrame>(new VideoFrame(iterator->first, read_jpeg((iterator++)->second)));
        }
        return std::unique_ptr<VideoFrame>(nullptr);
    }

}
