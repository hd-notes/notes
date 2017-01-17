/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  image.cpp -- pnm image manipulation
*/

#include "image.hpp"
#include <cassert>
#include <iostream>

Image chessboard(unsigned int width, unsigned int height,
                 unsigned int square_size) {
    Image i(width, height);
    for(unsigned int y = 0; y < height; y++) {
        for(unsigned int x = 0; x < width; x++) {
            if(y % (square_size * 2) < square_size) {
                if(x % (square_size * 2) < square_size) { i(x, y) = 255; }
            } else {
                if(x % (square_size * 2) >= square_size) { i(x, y) = 255; }
            }
        }
    }

    return i;
}

Image invert_image(Image const & image) {
    Image ret(image.width(), image.height());
    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            ret(x, y) = 255 - image(x, y);
        }
    }

    return ret;
}

int main() {
    Image i(4, 3);
    assert(i.width() == 4);
    assert(i.height() == 3);

    for(int x = 0; x < i.width(); x++) {
        for(int y = 0; y < i.height(); y++) { assert(i(x, y) == 0); }
    }

    assert(to_string(i) == std::string("0 0 0 0\n0 0 0 0\n0 0 0 0\n"));

    for(int x = 0; x < i.width(); x++) {
        for(int y = 0; y < i.height(); y++) {
            i(x, y) = 255 * ((x + 1 + y % 2) % 2);
        }
    }
    for(int x = 0; x < i.width(); x++) {
        for(int y = 0; y < i.height(); y++) {
            assert(i(x, y) == 255 * ((x + 1 + y % 2) % 2));
        }
    }
    assert(to_string(i) ==
           std::string("255 0 255 0\n0 255 0 255\n255 0 255 0\n"));
    writePGM(i, "board4x3.pgm");
    auto i2 = readPGM("board4x3.pgm");
    assert(i == i2);

    auto c1 = chessboard(400, 300, 20);
    writePGM(c1, "board400x300.pgm");
    auto c2 = readPGM("board400x300.pgm");
    assert(c1 == c2);
    writePGM(invert_image(c2), "board400x300-inverse.pgm");

	writePGM(invert_image(readPGM("lena.pgm")), "lena-invert.pgm");

}
