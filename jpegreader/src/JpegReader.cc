/*
 * JpegReader.cpp
 *
 *  Created on: 19.05.2016
 *      Author: ptriller
 */

#include "JpegReader.h"
#include "jpeglib.h"

JpegReader::~JpegReader() {

}

InputFrame * JpegReader::createFrame(const std::wstring &filename,
		unsigned long int timestamp) {
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	// Yay LAMBDA !!!
	jerr.error_exit = [](j_common_ptr cinfo) {throw cinfo->err;};
	try {
		jpeg_create_decompress(&cinfo);

		FILE *infile = _wfopen(filename.c_str(), L"rb");
		// TODO ERROR
		jpeg_stdio_src(&cinfo, infile);
		jpeg_read_header(&cinfo, TRUE);
		cinfo.jpeg_color_space = JCS_RGB;
		jpeg_start_decompress(&cinfo);

		// scanline reading .....
	} catch (struct jpeg_error_mgr *err) {
		char pszErr[1024];
		(cinfo.err->format_message)((j_common_ptr) &cinfo, pszErr);
	}
	jpeg_destroy_decompress(&cinfo);
	return NULL;
}
