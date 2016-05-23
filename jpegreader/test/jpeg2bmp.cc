#include "JpegReader.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>

namespace {
void writeUint32(std::ofstream &of, std::uint32_t value) {
	of << (unsigned char) (value & 0x000000ff);
	of << (unsigned char) ((value & 0x0000ff00) >> 8);
	of << (unsigned char) ((value & 0x00ff0000) >> 16);
	of << (unsigned char) ((value & 0xff000000) >> 24);
}

void writeUint16(std::ofstream &of, std::uint16_t value) {
	of << (unsigned char) (value & 0x000000ff);
	of << (unsigned char) ((value & 0x0000ff00) >> 8);
}

bool writeBMP(const VideoFrame &frame, const char *filename) {
	std::ofstream of(filename,
			std::ios::out | std::ios::binary | std::ios::trunc);
	if (!of.is_open()) {
		std::cerr << "Unable to open output File: " << std::strerror(errno)
				<< std::endl;
	}
	std::uint32_t rowSize = frame.width();
	std::uint32_t padding = 0;
	if (rowSize % 4 > 0) {
		padding = 4 - rowSize % 4;
		rowSize += padding;
	}
	std::uint32_t binarySize = frame.height() * rowSize * 3;

	of << "BM"; // 2
	writeUint32(of, binarySize + 54); //6
	writeUint32(of, 0); // 10
	writeUint32(of, 54); // 14
	writeUint32(of, 40); // 18
	writeUint32(of, frame.width()); // 22
	writeUint32(of, frame.height()); // 26
	writeUint16(of, 1); // 28
	writeUint16(of, 24); // 30
	writeUint32(of, 0); // 34
	writeUint32(of, binarySize); // 38
	writeUint32(of, 2835); // 42
	writeUint32(of, 2835); // 46
	writeUint32(of, 0); // 50
	writeUint32(of, 0); // 54
	for(int y = frame.height()-1; y >= 0; --y) {
		for(int x = 0; x < frame.width(); ++x) {
			const unsigned char *pixel = frame.get(x, y);
			of << pixel[2]; // B
			of << pixel[1]; // G
			of << pixel[0]; // R
		}
		for(int p = 0; p < padding;++p) {
			of << (unsigned char) 0;
		}
	}
	of.close();
	return true;
}

}

int main(int argc, const char * argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <input JPEG> <output BMP>"
				<< std::endl;
		return 1;
	}
	JpegReader reader;
	auto frame = reader.createFrame(argv[1], 0l);
	if (frame == NULL) {
		std::cerr << "Unable to load input file !" << std::endl;
	}
	if (writeBMP(*frame, argv[2])) {
		return 0;
	} else {
		std::cerr << "Unable to write output" << std::endl;
	}
	return 1;
}

