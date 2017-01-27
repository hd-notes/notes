/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  mandelbrot.cpp -- mandelbrot fractal
*/

#include "image.hpp"

#include <complex>
#include <iostream>

using cmplx = std::complex<double>;
using namespace std;

constexpr int max_norm = 1000;
constexpr int max_iter = 512;

class FractalView {
    double x_center_, y_center_, pixel_side_;

    int iterations_until_limit(cmplx const & c) const {
        cmplx z(0, 0);
        int   iters = 0;

        while((iters++ < max_iter) && (norm(z) < max_norm)) { z = z * z + c; }

        return iters;
    }

    cmplx pixel_to_real(cmplx p, cmplx cp, cmplx cr, double d) const {
        return (p - cp) * d + cr;
        /* return {(p.real() - cp.real()) * d + cr.x, (p.y - cp.y) * d + cr.y};
         */
    }

    cmplx pixel_to_complex(Image const & img, int ix, int iy) const {
        return pixel_to_real(cmplx(ix, iy),
                             cmplx(img.width() / 2, img.height() / 2),
                             cmplx(x_center_, y_center_), pixel_side_);
    }

    uint16_t color_scheme(int num_iterations) const {
        return 255 - (std::cbrt(num_iterations) / std::cbrt(max_iter)) * 255;
    };

public:
    double & x_center() { return x_center_; }

    double & y_center() { return y_center_; }

    double & pixel_side() { return pixel_side_; }

    void render_mandelbrot(Image & img) const {
        for(int y = 0; y < img.height(); y++) {
            for(int x = 0; x < img.width(); x++) {
                img(x, y) = color_scheme(
                    iterations_until_limit(pixel_to_complex(img, x, y)));
            }
        }
    }

public:
    FractalView(double x, double y, double d)
        : x_center_(x), y_center_(y), pixel_side_(d) {}
};

int main() {
    {
        FractalView v(0, 0, 4.0 / (640.0 / 2.0));
        Image       i(640, 480);
        v.render_mandelbrot(i);
        writePGM(i, "mandelbrot_overview.pgm");
    }

    bool        open   = true;
    double      x      = 0;
    double      y      = 0;
    double      zoom   = 4;
    double      width  = 640;
    double      height = 480;
    FractalView v(x, y, zoom / (width / 2.0));
    Image       i(width, height);
    while(open) {
        v.render_mandelbrot(i);
        writePGM(i, "mandelbrot.pgm");
        zoom = v.pixel_side();
        x    = v.x_center();
        y    = v.y_center();

        char in;
        std::cin >> in;

        switch(in) {
        case 'a': {
            v.x_center() -= (width / 4.0) * zoom;
            break;
        }
        case 'd': {
            v.x_center() += (width / 4.0) * zoom;
            break;
        }
        case 'w': {
            v.y_center() -= (height / 4.0) * zoom;
            break;
        }
        case 's': {
            v.y_center() += (height / 4.0) * zoom;
            break;
        }
        case '+': {
            v.pixel_side() /= 2;
            break;
        }
        case '-': {
            v.pixel_side() *= 2;
            break;
        }
        case 'b': {
            open = false;
            break;
        }
        default:
            break;
        }

        std::cout << v.x_center() << std::endl;
        std::cout << v.y_center() << std::endl;
        std::cout << v.pixel_side() << std::endl;
    }
}
