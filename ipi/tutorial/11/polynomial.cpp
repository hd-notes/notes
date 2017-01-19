#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class Polynomial {
    std::vector<int> a_;

public:
    // Konstruktor, dem die Koeffizienten als C-Array
    // uebergeben werden koennen, z.B.:
    //
    //     Polynomial p{1, 2, 3};
    Polynomial(std::initializer_list<int> coeffs) noexcept : a_{coeffs} {}

    // Konstruktor fuer ein Polynom vom Grad 0 (nur der konstante
    // Koeffizient ist definiert und hat den Wert 0).
    Polynomial() noexcept : Polynomial(0) {}

    // Konstruktor fuer ein Polynom vom Grad n, bei dem alle
    // Koeffizienten 0 sind. Der Fall n < 0 soll wie n == 0 behandelt
    // werden.
    Polynomial(int n) noexcept : a_(std::max(n, 0) + 1) {}

    // Grad des Polynoms (Exponent der hoechsten vorkommenden Potenz)
    int degree() const noexcept { return a_.size() > 0 ? a_.size() - 1 : 0; }

    // lesender Zugriff auf den Koeffizienten zur Potenz i
    int operator[](int i) const noexcept { return a_[i]; }

    // Lese-/Schreib-Zugriff auf den Koeffizienten zur Potenz i
    int & operator[](int i) noexcept { return a_[i]; }

    // Ausrechnen des Polynoms fuer das Argument x
    int operator()(int x) const noexcept {
        int y = 0;

        for(int i = a_.size(); i >= 0; i--) {
            y *= x;
            y += a_[i];
        }

        return y;
    }

    bool operator==(const Polynomial & other) const noexcept {
        return a_ == other.a_;
    }

    Polynomial operator+(const Polynomial & other) const noexcept {
        int        max_degree = std::max(other.degree(), degree());
        Polynomial p(max_degree);

        for(int i = 0; i <= max_degree; i++) { p[i] = a_[i] + other[i]; }

        return p;
    }

    Polynomial operator*(const Polynomial & other) const noexcept {
        int        new_degree = degree() + other.degree();
        Polynomial bigger     = degree() > other.degree() ? *this : other;
        Polynomial smaller    = degree() > other.degree() ? other : *this;
        Polynomial p(new_degree);

        for(int i = 0; i <= new_degree; i++) {
            int sum = 0;

            for(int x = std::max(i - smaller.degree(), 0); x <= bigger.degree();
                x++) {
                auto y = i - x;
                if(y < 0) continue;

                sum += bigger[x] * smaller[y];
            }
            p[i] = sum;
        }

        return p;
    }

    Polynomial derivative(int i = 1) const noexcept {
        Polynomial d(degree() - 1);

        for(int i = 0; i <= d.degree(); i++) { d[i] = (i + 1) * a_[i + 1]; }

        if(i == 1) {
            return d;
        } else {
            return d.derivative(i - 1);
        }
    }
};

int main() {
    // testen des Standard-Konstruktors
    Polynomial p0;
    assert(p0.degree() == 0);
    assert(p0[0] == 0);

    // testen des Konstruktors mit Gradangabe
    Polynomial pm(-1);
    assert(pm == p0);

    Polynomial p2(2);
    assert(p2.degree() == 2);

    // testen des Konstruktors mit Koeffizientenarray
    Polynomial p{1, 2, 3};
    assert(p.degree() == 2);

    // testen der Werte der Koeffizienten
    assert(p2[0] == 0);
    assert(p2[1] == 0);
    assert(p2[2] == 0);

    assert(p[0] == 1);
    assert(p[1] == 2);
    assert(p[2] == 3);

    // testen, dass die Polynom fuer verschiedene Argumente x
    // korrekt ausgerechnet werden
    assert(p0(1) == 0);
    assert(p0(2) == 0);
    assert(p0(3) == 0);

    assert(p2(1) == 0);
    assert(p2(2) == 0);
    assert(p2(3) == 0);

    assert(p(1) == 6);
    assert(p(2) == 17);
    assert(p(3) == 34);

    // testen der Polynom-Addition
    Polynomial pa1 = p + p;
    Polynomial pa1_expected{2, 4, 6};
    assert(pa1 == pa1_expected);

    Polynomial pa2 = p + Polynomial{3, 6};
    Polynomial pa2_expected{4, 8, 3};
    assert(pa2 == pa2_expected);

    // testen der Polynom-Multiplikation
    Polynomial pm1 = p * p;
    assert(pm1.degree() == 4);
    assert(pm1(2) == p(2) * p(2));
    Polynomial pm1_expected{1, 4, 10, 12, 9};
    assert(pm1 == pm1_expected);

    Polynomial pm2 = p * Polynomial{2, 6};
    assert(pm2.degree() == 3);
    Polynomial pm2_expected{2, 10, 18, 18};
    assert(pm2 == pm2_expected);

    // testen der ersten Ableitung
    Polynomial derivative1_expected{2, 6};
    assert(p.derivative() == derivative1_expected);
    assert(p.derivative(1) == derivative1_expected);

    // testen der zweiten bis vierten Ableitung
    Polynomial derivative2_expected{6};
    assert(p.derivative(2) == derivative2_expected);
    Polynomial derivative3_expected{0};
    assert(p.derivative(3) == derivative3_expected);
    assert(p.derivative(4) == derivative3_expected);

    std::cout << "Alle Tests erfolgreich!\n";
}
