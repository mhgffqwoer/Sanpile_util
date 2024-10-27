#pragma once
#include <fstream>
#include "../Table/Table.hpp"

namespace Sandpile {

static constexpr const uint8_t kFileHeaderSize = 14;
static constexpr const uint8_t kInfoHeaderSize = 40;
static constexpr const uint8_t kPaletteSize = 20;
static constexpr const uint8_t kColorAmount = 5;
static constexpr const uint8_t kBitsPerPixel = 4;

struct Color {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

struct Palette {
    uint8_t palette[kPaletteSize] {0};

    Color white = {255, 255, 255};  //  0
    Color green = {10, 85, 71};  //  1
    Color yellow = {5, 178, 252};  //  2
    Color purple = {159, 83, 134};  //  3
    Color black = {31, 29, 39};  //  4

    void SetPalette();
};

struct Image {
    uint8_t* pixels;
    uint32_t file_size;
    uint8_t* bmp_file_header;
    uint8_t* bmp_inf_header;
    uint8_t padding_amount;

    void SetFileSize(Table& table);
    void SetHeader(Table& table);
    void SetColors(Table& table);
    void CreateImage(Table& table, const std::string& output_filename);
};

}  // namespace Sandtable