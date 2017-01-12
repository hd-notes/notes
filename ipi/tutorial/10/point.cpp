#include <cassert>
#include <iostream>
#include <string>

class Point {
private:
    // die Koordinaten des Punktes
    double x_;
	double y_;

public:
	// Standardkonstruktor: initialisiere Punkt (0,0)
	Point() : x_(0), y_(0) {}

    // Konstruktor mit zwei Koordinaten: initialisiere Punkt (x,y)
	Point(double x, double y) : x_(x), y_(y) {}

    // Getter-Funktionen fuer die Koordinaten
	double x() const { return (*this).x_; }

	double y() const { return (*this).y_; }

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
        Point res((*this).y(), (*this).x());
        return res;
    }

    // erzeuge neuen Punkt, der um den Vektor v verschoben ist
	Point translate(Point const & v) const {
        Point res((*this).x() + v.x(), (*this).y() + v.y());
        return res;
    }
};

// wandle den Punkt in einen String der Form "[x, y]"
std::string to_string(Point const & p) {
    return "[" + std::to_string(p.x()) + ", " + std::to_string(p.y()) + "]";
}

Point operator+(Point p1, Point p2) {
	return {p1.x() + p2.x(), p1.y() + p2.y()};
}

Point operator-(Point p1, Point p2) {
	return {p1.x() - p2.x(), p1.y() - p2.y()};
}

Point operator*(Point p1, Point p2) {
	return {p1.x() * p2.x(), p1.y() * p2.y()};
}

Point operator/(Point p1, Point p2) {
	return {p1.x() / p2.x(), p1.y() / p2.y()};
}

Point operator*(double s, Point p) {
	return {s * p.x(), s * p.y()};
}

Point operator*(Point p, double s) {
	return {p.x() * s, p.y() * s};
}

Point operator/(Point p, double s) {
	return {p.x() / s, p.y() / s};
}

Point operator-(Point p) {
	return {-p.x(), -p.y()};
}

void test_Point() {
	using P = Point;

	Point p(2, 3), q(4, 5);
	assert(p + q == Point(6, 8));
	assert(p - q == Point(-2, -2));
	assert(p * q == Point(8, 15));
	assert(p / q == Point(0.5, 3.0 / 5.0));
	assert(p * 0 == Point(0, 0));
	assert(p * 1 == p);
	assert(p * -1 == Point(0, 0) - p);
	assert(0 * p == p * 0);
	assert(1 * p == p * 1);
	assert(-1 * p == p * -1);
	assert(p / 1 == p);
	assert(q / 2 == Point(2, 2.5));
	assert(2 * q / 2 == q);
	assert(-p == Point(0, 0) - p);
	assert(-q == Point(0, 0) - q);
	assert(-p + p == Point(0, 0));

	p = {1, 4};
	q = {2, 3};
	assert((p + q) == Point(3, 7));
	assert((p - q) == Point(-1, 1));
	assert((p * q) == Point(2, 12));
	assert((p / q) == Point(0.5, 4.0 / 3.0));

	p = {199, 123};
	q = {121, 144};
	assert((p + q) == Point(320, 267));
	assert((p - q) == Point(78, -21));
	assert((p * q) == Point(24079, 17712));
	assert((p / q) == Point(199.0 / 121.0, 123.0 / 144.0));

    std::cout << "Alle Tests erfolgreich.\n";
}

int main() { test_Point(); }
