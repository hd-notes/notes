/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  conway.cpp -- conway game of life
*/

#include "image.hpp"

#include <cassert>
#include <cstdio>
#include <iostream>

int get_periodic(int x, int width) { return ((x % width) + width) % width; }

int count_alive_neighbors(Image const & image, int x, int y) {
    int count = 0;
    count += image.get_periodic(x + 1, y + 1) ? 0 : 1;
    count += image.get_periodic(x + 0, y + 1) ? 0 : 1;
    count += image.get_periodic(x - 1, y + 1) ? 0 : 1;

    count += image.get_periodic(x + 1, y - 0) ? 0 : 1;
    count += image.get_periodic(x - 1, y - 0) ? 0 : 1;

    count += image.get_periodic(x + 1, y - 1) ? 0 : 1;
    count += image.get_periodic(x + 0, y - 1) ? 0 : 1;
    count += image.get_periodic(x - 1, y - 1) ? 0 : 1;

    return count;
}

Image conway_step(Image const & image) {
    Image n(image.width(), image.height());
    int   ns = 0;

    for(int y = 0; y < image.height(); y++) {
        for(int x = 0; x < image.width(); x++) {
            ns = count_alive_neighbors(image, x, y);

            if(image(x, y)) {
                if(ns != 3) { n(x, y) = 255; }
            } else {
                if((ns < 2) || (ns > 3)) { n(x, y) = 255; }
            }
        }
    }

    return n;
}

Image scale_image(Image const & image, int scale) {
    Image n(image.width() * scale, image.height() * scale);

    for(int y = 0; y < n.height(); y++) {
        for(int x = 0; x < n.height(); x++) {
            n(x, y) = image(x / scale, y / scale);
        }
    }

    return n;
}

int main() {
    {
        auto init = readPGM("conway_init.pgm");
        char buffer[19];

        for(int i = 0; i < 100; i++) {
            init = conway_step(init);
            std::snprintf(buffer, 19, "conway_sim_%03d.pgm", i);
            writePGM(scale_image(init, 5), buffer);
        }
        init = scale_image(init, 5);
        assert(init == readPGM("conway_test.pgm"));
    }

    auto init = readPGM("my_conway.pgm");
    char buffer[23];

    for(int i = 0; i < 1103; i++) {
        init = conway_step(init);
        std::snprintf(buffer, 23, "my_conway_sim_%04d.pgm", i);
        writePGM(scale_image(init, 5), buffer);
		std::cout << buffer << std::endl;
    }
	 
}
