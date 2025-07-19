#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

#pragma pack(push, 1)

struct BMPHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

struct DIBHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorUsed;
    uint32_t colorImportant;
};

struct Image {
    int width;
    int height;
    int channels;
    std::vector<uint8_t> data;
};

#pragma pack(pop)