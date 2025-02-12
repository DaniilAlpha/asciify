#include "image/bitmap/codec/bitmap_codec.hpp"

#include <fstream>

#include "image/bitmap/codec/jpeg_codec.hpp"
#include "image/bitmap/codec/webp_codec.hpp"

Bitmap *BitmapCodec::decode(char const *const filename) {
    static_assert(
        sizeof(char) == sizeof(uint8_t),
        "This code is expected to work on 1-byte chars only."
    );

    letmut src = std::ifstream(filename, std::ios::binary);
    src.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    src.seekg(0, std::ios::end);
    let src_size = src.tellg();
    src.seekg(0, std::ios::beg);

    let src_data = new uint8_t[src_size]();
    src.read(reinterpret_cast<char *>(src_data), src_size);

    let decoders = {WebpCodec::decode, JpegCodec::decode};
    for (let &decode : decoders) {
        try {
            let image = decode(src_data, src_size);

            delete[] src_data;
            return image;
        } catch (std::exception const &) { continue; }
    }

    delete[] src_data;
    throw UnsupportedFormatException();
}
