#ifndef ASCII_ART_HPP
#define ASCII_ART_HPP

#include <algorithm>

#include "color.hpp"
#include "dims.hpp"
#include "image/image.hpp"

struct AsciiEl {
    AsciiEl() : AsciiEl(' ') {}

    explicit AsciiEl(char const c, Color const &color = Color(0xFFFFFF))
    : c(c), _true_color(color), _indexed_color_index(color_to_indexed(color)) {}

    char c;

    constexpr unsigned indexed_color_index() const {
        return _indexed_color_index;
    }
    constexpr Color true_color() const { return _true_color; }

    void set_true_color(Color const &value) {
        _true_color = value;
        _indexed_color_index = color_to_indexed(value);
    }

   private:
    static constexpr Color const indexed_colors[] = {
#ifdef _MSC_BUILD
        // windows console colors
        Color::rgb255(12, 12, 12),
        Color::rgb255(197, 15, 31),
        Color::rgb255(19, 161, 14),
        Color::rgb255(193, 156, 0),
        Color::rgb255(0, 55, 218),
        Color::rgb255(136, 23, 152),
        Color::rgb255(58, 150, 221),
        Color::rgb255(204, 204, 204),
#else
        // xterm colors
        Color::rgb24(0, 0, 0),
        Color::rgb24(205, 0, 0),
        Color::rgb24(0, 205, 0),
        Color::rgb24(205, 205, 0),
        Color::rgb24(0, 0, 238),
        Color::rgb24(205, 0, 205),
        Color::rgb24(0, 205, 205),
        Color::rgb24(229, 229, 229),
#endif
    };

    Color _true_color;
    unsigned _indexed_color_index;

    static constexpr unsigned color_to_indexed(Color const &color) {
        return std::min_element(
                   indexed_colors,
                   indexed_colors + lenof(indexed_colors),
                   [&color](Color const &a, Color const &b) {
                       return (a - color).sqr_magnitude() <=
                              (b - color).sqr_magnitude();
                   }
               ) -
               indexed_colors;
    }
};

class AsciiArt : public Image<AsciiEl> {
   public:
    AsciiArt(Image<Color> const &image, Size const char_size)
    : Image<AsciiEl>(image.size() / char_size), _image(image) {}

    Image<Color> const &image() const { return _image; }

   private:
    Image<Color> const &_image;
};

#endif
