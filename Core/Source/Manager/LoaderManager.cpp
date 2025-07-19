#include "LoaderManager.h"

#include <fstream>

Image* LoaderManager::loadBMP(const char* filePath) {
	std::ifstream file(filePath, std::ios::binary);

	if (!file) {
		throw std::runtime_error("Could not open BMP file: " + std::string(filePath));
		return nullptr;
	}

	BMPHeader bmpHeader;
	DIBHeader dibHeader;

	file.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

	if (bmpHeader.signature != 0x4D42) { // 'BM' in little-endian
		throw std::runtime_error("Not a valid BMP file: " + std::string(filePath));
		return nullptr;
	}

	file.read(reinterpret_cast<char*>(&dibHeader), sizeof(DIBHeader));
	
	if (dibHeader.bitPerPixel != 24 && dibHeader.bitPerPixel != 32) {
		throw std::runtime_error("Unsupported BMP format: " + std::string(filePath));
		return nullptr;
	}

	int width = dibHeader.width;
	int height = std::abs(dibHeader.height);
	int channels = (dibHeader.bitPerPixel / 8);
	size_t rowSize = ((dibHeader.bitPerPixel * width + 31) / 32) * 4; // row padding
	size_t dataSize = rowSize * height;

	std::vector<uint8_t> data(dataSize);
	file.seekg(bmpHeader.dataOffset, std::ios::beg);
	file.read(reinterpret_cast<char*>(data.data()), dataSize);

	std::vector<uint8_t> imageData(width * height * channels);

	for (int y = 0; y < height; ++y) {
		int row = dibHeader.height > 0 ? (height - 1 - y) : y; // BMP stores bottom-up
		memcpy(
			&imageData[y * width * channels],
			&data[row * rowSize],
			width * channels
		);
	}

	Image* img = new Image();
	img->width = width;
	img->height = height;
	img->channels = channels;
	img->data = std::move(imageData);

	return img;
}