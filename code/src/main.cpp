/*
refs:
    - inspiration & everything:
        - https://www.youtube.com/watch?v=gg40RWiaHRY
    - gradients:
        - https://paulbourke.net/dataformats/asciiart/
        - https://www.youtube.com/watch?v=n4zUgtDk95w
*/

#include <iostream>

#include "conviniences.hpp"
#include "effect/effect.hpp"
#include "image/jpeg_image.hpp"
#include "image/webp_image.hpp"

int main() {
    let image = WebpImage("test.webp");
    // let image = JpegImage("test.jpeg");
    // THIS IS INVALID FIX LATER
    letmut ascii_art = AsciiArt(image.get_size(), Size(10, 22) / 1.5);

    std::cout << image.get_size().w << "x" << image.get_size().h << "\n";

    let effect = LuminanceAsciiEffect();
    effect(image, ascii_art);

    std::cout << ascii_art;

    return 0;
}
