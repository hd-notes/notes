/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  koordinaten.cpp -- coodinate transformations
*/

#include <cassert>
#include <cmath>
#include <iostream>

#include "image.hpp"

template <typename T>
struct v2 {
    T x;
    T y;
};

/*
  Die Formel ist
  x = (ix - cx)d + x_{center}
  y = (iy - cy)d + y_{center}
*/

v2<double> pixel_to_real(v2<int> p, v2<int> cp, v2<double> cr, double d) {
    return {(p.x - cp.x) * d + cr.x, (p.y - cp.y) * d + cr.y};
}

template <typename T>
inline auto sq(T && t) noexcept {
    return t * t;
}

int main() {
    Image i1(640, 480), i2 = i1;

    for(int y = 0; y < i1.height(); y++) {
        for(int x = 0; x < i1.width(); x++) {
            auto real = pixel_to_real({x, y}, {i1.width() / 2, i2.height() / 2},
                                      {0, 0}, 1.0 / 64.0);
            i1(x, y) = 255.0 * sq(std::sin(sq(real.x) + sq(real.y)));
            real = pixel_to_real({x, y}, {i1.width() / 2, i2.height() / 2},
                                 {0, 0}, 1);
            i2(x, y) = 255.0 * sq(std::sin((sq(real.x) + sq(real.y)) / 4096.0));
        }
    }

    assert(i1 == i2);

    writePGM(i1, "koordinaten.pgm");
}
