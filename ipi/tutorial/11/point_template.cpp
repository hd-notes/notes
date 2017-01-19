#include <cassert>
#include <iostream>
#include <string>

template <typename T>
class Point {
private:
    // die Koordinaten des Punktes
    T x_;
    T y_;

public:
    // Standardkonstruktor: initialisiere Punkt (0,0)
    Point() : x_(0.0), y_(0.0) {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
    Point(T x, T y) : x_(x), y_(y) {}

    // Getter-Funktionen fuer die Koordinaten
    T x() const { return (*this).x_; }

    T y() const { return (*this).y_; }

    // teste ob zwei Punkte gleich sind
    bool operator==(Point const & other) const {
        return (*this).x() == other.x() && (*this).y() == other.y();
    }

    // teste ob zwei Punkte ungleich sind
    bool operator!=(Point const & other) const {
        return (*this).x() != other.x() || (*this).y() != other.y();
    }

    // erzeuge neuen Punkt, desssen x- und y-Koordinate
    // vertauscht sind
    Point transpose() const {
        Point<T> res((*this).y(), (*this).x());
        return res;
    }

    // erzeuge neuen Punkt, der um den Vektor v verschoben ist
    Point translate(Point const & v) const {
        Point<T> res((*this).x() + v.x(), (*this).y() + v.y());
        return res;
    }
};

template <typename T>
std::string to_string(Point<T> const & p) {
    return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

template <typename T>
Point<T> operator+(Point<T> p1, Point<T> p2) {
    Point<T> res(p1.x() + p2.x(), p1.y() + p2.y());
    return res;
}

template <typename T>
Point<T> operator-(Point<T> p1, Point<T> p2) {
    Point<T> res(p1.x() - p2.x(), p1.y() - p2.y());
    return res;
}

template <typename T>
Point<T> operator-(Point<T> p) {
    Point<T> res(-p.x(), -p.y());
    return res;
}

template <typename T>
Point<T> operator*(Point<T> p1, Point<T> p2) {
    Point<T> res(p1.x() * p2.x(), p1.y() * p2.y());
    return res;
}

template <typename T>
Point<T> operator*(T s, Point<T> p) {
    Point<T> res(s * p.x(), s * p.y());
    return res;
}

template <typename T>
Point<T> operator*(Point<T> p, T s) {
    Point<T> res(p.x() * s, p.y() * s);
    return res;
}

template <typename T>
Point<T> operator/(Point<T> p1, Point<T> p2) {
    Point<T> res(p1.x() / p2.x(), p1.y() / p2.y());
    return res;
}

template <typename T>
Point<T> operator/(Point<T> p, T d) {
    Point<T> res(p.x() / d, p.y() / d);
    return res;
}

void test_Point_double() {
    using P = Point<double>;

    P p(2.0, 3.0), q(4.0, 5.0);
    assert(p + q == P(6.0, 8.0));
    assert(p - q == P(-2.0, -2.0));
    assert(p * q == P(8.0, 15.0));
    assert(p / q == P(0.5, 3.0 / 5.0));
    assert(p * 0.0 == P(0.0, 0.0));
    assert(p * 1.0 == p);
    assert(p * -1.0 == P(0.0, 0.0) - p);
    assert(0.0 * p == p * 0.0);
    assert(1.0 * p == p * 1.0);
    assert(-1.0 * p == p * -1.0);
    assert(p / 1.0 == p);
    assert(q / 2.0 == P(2.0, 2.5));
    assert(2.0 * q / 2.0 == q);
    assert(-p == P(0.0, 0.0) - p);
    assert(-q == P(0.0, 0.0) - q);
    assert(-p + p == P(0.0, 0.0));

    p = {1.0, 4.0};
    q = {2.0, 3.0};
    assert((p + q) == P(3.0, 7.0));
    assert((p - q) == P(-1.0, 1.0));
    assert((p * q) == P(2.0, 12.0));
    assert((p / q) == P(0.5, 4.0 / 3.0));

    p = {199.0, 123.0};
    q = {121.0, 144.0};
    assert((p + q) == P(320.0, 267.0));
    assert((p - q) == P(78.0, -21.0));
    assert((p * q) == P(24079.0, 17712.0));
    assert((p / q) == P(199.0 / 121.0, 123.0 / 144.0));

    std::cout << "Alle Tests erfolgreich.\n";
}

void test_Point_int() {
    using P = Point<int>;

    P p(2, 3), q(4, 5);
    assert(p + q == P(6, 8));
    assert(p - q == P(-2, -2));
    assert(p * q == P(8, 15));
    assert(p / q == P(0.5, 3.0 / 5.0));
    assert(p * 0 == P(0, 0));
    assert(p * 1 == p);
    assert(p * -1 == P(0, 0) - p);
    assert(0 * p == p * 0);
    assert(1 * p == p * 1);
    assert(-1 * p == p * -1);
    assert(p / 1 == p);
    assert(q / 2 == P(2, 2.5));
    assert(2 * q / 2 == q);
    assert(-p == P(0, 0) - p);
    assert(-q == P(0, 0) - q);
    assert(-p + p == P(0, 0));

    p = {1, 4};
    q = {2, 3};
    assert((p + q) == P(3, 7));
    assert((p - q) == P(-1, 1));
    assert((p * q) == P(2, 12));
    assert((p / q) == P(0.5, 4.0 / 3.0));

    p = {199, 123};
    q = {121, 144};
    assert((p + q) == P(320, 267));
    assert((p - q) == P(78, -21));
    assert((p * q) == P(24079, 17712));
    assert((p / q) == P(199.0 / 121.0, 123.0 / 144.0));

    std::cout << "Alle Tests erfolgreich.\n";
}

int main() {
    test_Point_double();
    test_Point_int();
}
