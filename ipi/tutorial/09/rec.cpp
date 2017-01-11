/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  rec.cpp -- Rectangle class
*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Rectangle;
std::string to_string(Rectangle const & r);

/////////////////////////////////////////////////
// die 2-dimensionale Punkt-Klasse aus der Vorlesung
class Point {
	// die Koordinaten des Punktes
	double x_;
	double y_;

public:
	// Standardkonstruktor: initialisiere Punkt (0,0)
	Point() : x_(0.0), y_(0.0) {}

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

/////////////////////////////////////////////////
// Implementieren Sie die Rectangle-Klasse.
class Rectangle {
	Point p0_; // linke untere Ecke
	Point p1_; // rechte obere Ecke

public:
	// Implementieren Sie die folgenden Konstruktoren.
	Rectangle() {}

	Rectangle(Point const & p1) : p1_(p1) {}

	Rectangle(Point const & p0, Point const & p1) : p0_(p0), p1_(p1) {}

	// teste ob zwei Rechtecke gleich sind
	bool operator==(Rectangle const & other) const {
		return (p0_ == other.p0()) && (p1_ == other.p1());
	}

	// read-only Getter-Funktionen fuer die Member-Variablen
	Point const & p0() const { return (*this).p0_; }

	Point const & p1() const { return (*this).p1_; }

	// Implementieren Sie die folgenden Getter-Funktionen.
	double x0() const // linke x-Koordinate
	{
		return p0_.x();
	}

	double x1() const // rechte x-Koordinate
	{
		return p1_.x();
	}

	double y0() const // untere y-Koordinate
	{
		return p0_.y();
	}

	double y1() const // obere  y-Koordinate
	{
		return p1_.y();
	}

	double width() const // Breite
	{
		return x1() - x0();
	}

	double height() const // Hoehe
	{
		return y1() - y0();
	}

	// Implementieren Sie eine Funktion, die genau dann 'true'
	// zurueckgibt, wenn das Rechteck nicht ungueltig ist.
	bool is_valid() const { return (x0() <= x1()) && (y0() <= y1()); }

	// Implementieren Sie eine Funktion, die die Flaeche des
	// Rechtecks zurueckgibt, bzw. -1.0, wenn das Rechteck
	// ungueltig ist.
	double area() const { return is_valid() ? width() * height() : -1; }

	// Implementieren Sie eine Funktion, die ein neues Rechteck
	// zurueckgibt, bei dem die x- und y-Koordinaten vertauscht sind.
	Rectangle transpose() const {
		return Rectangle(p0_.transpose(), p1_.transpose());
	}

	// Implementieren Sie eine Funktion, die ein neues Rechteck
	// zurueckgibt, das um den Vektor v verschoben ist.
	Rectangle translate(Point const & v) const {
		return Rectangle(p0_.translate(v), p1_.translate(v));
	}

	// Implementieren Sie eine Funktion, die genau dann 'true'
	// zurueckgibt, wenn der Punkt p im Rechteck (*this) enthalten
	// ist. Wenn (*this) ungueltig ist, soll 'false' zurueckgegeben
	// werden.
	bool contains(Point const & p) const {
		return is_valid()
				   ? (p.x() >= x0()) && (p.x()) <= x1() && (p.y() >= y0()) &&
						 (p.y()) <= y1()
				   : false;
	}

	// Implementieren Sie eine Funktion, die genau dann 'true'
	// zurueckgibt, wenn das Rechteck r im Rechteck (*this) enthalten
	// ist. Wenn (*this) oder r ungueltig sind, soll 'false' zurueckgegeben
	// werden.
	bool contains(Rectangle const & r) const {
		return (is_valid() && r.is_valid())
				   ? (contains(r.p0()) && contains(r.p1()))
				   : false;
	}
};

// Implementieren Sie eine Funktion, die das Rechteck
// in einen String der Form "[x0:x1, y0:y1]" umwandelt.
std::string to_string(Rectangle const & r) {
	std::string       s;
	std::stringstream ss(s);
	ss << "[" << r.x0() << ":" << r.x1() << ", " << r.y0() << ":" << r.y1()
	   << "]";
	return ss.str();
}

// Implementieren Sie eine Funktion, die das kleinste Rechteck
// zurueckgibt, das r1 und r2 enthaelt.
Rectangle rectangle_union(Rectangle const & r1, Rectangle const & r2) {
	return {{std::min(r1.x0(), r2.x0()), std::min(r1.y0(), r2.y0())},
			{std::max(r1.x1(), r2.x1()), std::max(r1.y1(), r2.y1())}};
}

// Implementieren Sie eine Funktion, die den Durchschnitt
// der Rechtecke r1 und r2 zerueckgibt, oder ein beliebiges
// ungueltiges Rechteck, falls r1 und r2 nicht ueberlappen.
Rectangle rectangle_intersection(Rectangle const & r1, Rectangle const & r2) {
	return{{std::max(r1.x0(), r2.x0()), std::max(r1.y0(), r2.y0())},
			{std::min(r1.x1(), r2.x1()), std::min(r1.y1(), r2.y1())}};
}

// Implementieren Sie Tests fuer die Rectangle-Klasse.
void testRectangle() {
	Rectangle r0(Point(3.0, 5.0));

	assert(r0.p0() == Point(0.0, 0.0));
	assert(r0.p1() == Point(3.0, 5.0));
	assert(r0.is_valid());
	assert(r0.area() == 15);
	assert(r0.transpose() == Rectangle({5, 3}));
	assert(r0.translate({0, 0}) == r0);

	Rectangle r(Point(1.0, 2.0), Point(3.0, 5.0));
	assert(r.x0() == 1.0);
	assert(r.width() == 2);
	assert(r.height() == 3);
	assert(r.is_valid());
	assert(r.area() == 6);
	assert(r.transpose() == Rectangle({2, 1}, {5, 3}));
	assert(r.translate({0, 2}) == Rectangle({1, 4}, {3, 7}));

	Rectangle r2;
	assert(r2.x0() == 0);
	assert(r2.x1() == 0);
	assert(r2.y0() == 0);
	assert(r2.y1() == 0);
	assert(to_string(r2) == "[0:0, 0:0]");
	assert(r2.width() == 0);
	assert(r2.height() == 0);
	assert(r2.is_valid());
	assert(r2.area() == 0);
	assert(r2.transpose() == Rectangle());
	assert(r2.translate({2, 2}) == Rectangle({2, 2}, {2, 2}));

	assert(r0.contains(r));
	assert(r0.contains(r2));
	assert(r.contains(r));
	assert(!r.contains(r2));
	assert(!r2.contains(r));
	assert(!Rectangle({-1, -1}).contains(r2));

	assert(r0.contains(r.p0()));
	assert(r0.contains(r.p1()));
	assert(r.contains(r.p0()));
	assert(r.contains(r.p1()));
	assert(!r2.contains(r.p0()));
	assert(!r2.contains(r.p1()));

	Rectangle r3{{1, 2}};
	assert(r3.x0() == 0);
	assert(r3.x1() == 1);
	assert(r3.y0() == 0);
	assert(r3.y1() == 2);
	assert(to_string(r3) == "[0:1, 0:2]");
	assert(r3.width() == 1);
	assert(r3.height() == 2);
	assert(r3.is_valid());
	assert(r3.area() == 2);
	assert(r3.transpose() == Rectangle({2, 1}));
	assert(r3.translate({-1, 0}) == Rectangle({-1, 0}, {0, 2}));

	Rectangle r4{{1, 2}, {3, 4}};
	assert(r4.x0() == 1);
	assert(r4.x1() == 3);
	assert(r4.y0() == 2);
	assert(r4.y1() == 4);
	assert(to_string(r4) == "[1:3, 2:4]");
	assert(r4.width() == 2);
	assert(r4.height() == 2);
	assert(r4.is_valid());
	assert(r4.area() == 4);
	assert(r4.transpose() == Rectangle({2, 1}, {4, 3}));
	assert(r4.translate({1, 0}) == Rectangle({2, 2}, {4, 4}));

	assert(!Rectangle({3, 4}, {1, 2}).is_valid());
	assert(Rectangle({3, 4}, {1, 2}).area() == -1);
	assert(Rectangle({10, 9}, {11, 10}).transpose() ==
		   Rectangle({9, 10}, {10, 11}));
	assert(Rectangle({10, 9}, {11, 10}).translate({-1, -1}) ==
		   Rectangle({9, 8}, {10, 9}));

	assert(rectangle_union(r2, r3) == r3);
	assert(rectangle_union(r2, r4) == Rectangle({3, 4}));
	assert(rectangle_union(r3, r4) == Rectangle({3, 4}));
	assert(rectangle_union(r4, r0) == r0);

	assert(rectangle_intersection(r2, r3) == r2);
	assert(rectangle_intersection(r, r4) == r4);
	assert(rectangle_intersection(r, r0) == r);
	assert(rectangle_intersection(r0, r2) == r2);

	// Fuegen Sie weitere Tests entsprechend der Aufgabe hinzu.

	std::cout << "alle Rectangle-Tests erfolgreich\n";
}
