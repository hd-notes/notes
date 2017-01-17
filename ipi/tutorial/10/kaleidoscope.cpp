/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  kaleidoscope.cpp -- Image mirroring
*/

#include <cassert>
#include "image.hpp"

Image mirror_x(Image const & image) {
	Image r(image.width() * 2, image.height());

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            r(x, y) = image(x, y);
            r(r.width() - x - 1, y) = image(x, y);
        }
    }

	return r;
}

Image mirror_y(Image const & image) {
	Image r(image.width(), image.height() * 2);

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            r(x, y) = image(x, y);
            r(x, r.height() - y - 1) = image(x, y);
        }
    }

	return r;
}

Image mirror_d(Image const & image) {
	Image r(image.height(), image.width());

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
			if(x > y) {
				r(x, y) = image(y, x);
			} else {
				r(x, y) = image(x, y);
			}
        }
    }

	return r;
}

void assert_equal(Image const & i, std::string filename) {
	assert(i == readPGM(filename));
}

Image kaleidoscope4(Image const & image) {
	return mirror_y(mirror_x(image));
}

Image kaleidoscope8(Image const & image) {
	return mirror_y(mirror_x(mirror_d(image)));
}

int main() {
	assert_equal(mirror_x(readPGM("lena.pgm")), "mirror_x_test.pgm");
	assert_equal(mirror_y(readPGM("lena.pgm")), "mirror_y_test.pgm");
	assert_equal(kaleidoscope4(readPGM("lena.pgm")), "kaleidoskop4_test.pgm");
	assert_equal(kaleidoscope8(readPGM("lena.pgm")), "kaleidoskop8_test.pgm");
	writePGM(kaleidoscope8(readPGM("my_image.pgm")), "my_kaleidoscope.pgm");
}
