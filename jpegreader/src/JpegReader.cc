/*
 * JpegReader.cpp
 *
 *  Created on: 19.05.2016
 *      Author: ptriller
 */

#include "JpegReader.h"
#include "jpeglib.h"
#include <iostream>
#include <cstdio>
#include <cstring>

JpegReader::~JpegReader() {

}

std::unique_ptr<VideoFrame> JpegReader::createFrame(const std::string &filename,
		unsigned long int timestamp) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = [](j_common_ptr cinfo) {throw cinfo->err;};
	try {
		jpeg_create_decompress(&cinfo);
		FILE *infile = std::fopen(filename.c_str(), "rb");
		if(infile == NULL) {
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
		unsigned int width = cinfo.output_width;
		unsigned int height = cinfo.output_height;
		std::unique_ptr<VideoFrame> frame(new VideoFrame(width, height, timestamp));
		while (cinfo.output_scanline < height) {
			unsigned char *buffer_array[1];
			buffer_array[0] = frame->buffer() + width * cinfo.output_scanline * 3;
			jpeg_read_scanlines(&cinfo, buffer_array, 1);
		}
		jpeg_finish_decompress(&cinfo);
		fclose(infile);
		//TODO ERROR
		jpeg_destroy_decompress(&cinfo);
		return frame;
	} catch (struct jpeg_error_mgr *err) {
		char pszErr[JMSG_LENGTH_MAX];
		(cinfo.err->format_message)((j_common_ptr) &cinfo, pszErr);
		std::cerr << "Error: " << pszErr << std::endl;
		jpeg_destroy_decompress(&cinfo);
		return NULL;
	}
}
