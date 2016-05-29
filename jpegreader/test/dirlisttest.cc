#include "DirectoryReader.h"
#include <iostream>

int main(int argc, const char * argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <directory>"	<< std::endl;
		return 1;
	}
	DirectoryReader reader(argv[1]);
	int b;
	std::cin >> b;
	return 0;
}
