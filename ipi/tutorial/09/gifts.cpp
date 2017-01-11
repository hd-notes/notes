/*
  Copyright (C) 2017 by Robin Heinemann. All Rights Reserved.
  gifts.cpp -- optimal gift placing
*/

#include <array>
#include <iterator>
#include <limits>
#include <vector>

// clang-format off
#include "rec.cpp"
#include "gifts.txt"
// clang-format on

using namespace std;
template <typename T>
using vec            = vector<T>;
using str            = string;
constexpr auto infty = std::numeric_limits<double>::infinity();

template <typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & v) {
	if(!v.empty()) {
		out << '[';
		std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
		out << "\b\b]";
	}
	return out;
}

std::ostream & operator<<(std::ostream & out, const Rectangle & r) {
	return out << to_string(r);
}

template <typename T, int size>
auto to_vec(T (&data)[size]) {
	vec<T> vector;
	vector.assign(data, data + size);
	return vector;
}
double bssf_score(Rectangle const & free, Rectangle const & obj) {
	auto dw = free.width() - obj.width();
	auto dh = free.height() - obj.height();
	auto m  = std::min(dw, dh);

	return m > 0 ? m : infty;
}

struct placeable {
	const Rectangle & free;
	const Rectangle & to_place;
	double            score;
	bool              transposed;
};

int main() {
	vec<Rectangle> to_be_placed(gifts), already_placed,
		free_rectangles = {table};
	to_be_placed.push_back(tree_stand);

	bool did_place_stand = false;

	while(true) {
		vec<placeable> can_place;
		for(const auto & free : free_rectangles) {
			for(const auto & to_place : to_be_placed) {
				auto score = bssf_score(free, to_place);
				if(score != infty) {
					can_place.push_back(
						placeable{free, to_place, score, false});
				}
			}
		}

		for(const auto & free : free_rectangles) {
			for(const auto & to_place : to_be_placed) {
				auto score = bssf_score(free, to_place.transpose());
				if(to_place == tree_stand) {
					can_place.push_back(placeable{free, to_place, 0, true});
				} else if(score != infty) {
					can_place.push_back(placeable{free, to_place, score, true});
				}
			}
		}

		if(can_place.size() == 0) break;

		placeable best =
			*min_element(can_place.begin(), can_place.end(),
						 [](auto r1, auto r2) { return r1.score < r2.score; });

		if(best.to_place == tree_stand) did_place_stand = true;

		auto new_rect =
			best.transposed ? best.to_place.transpose() : best.to_place;
		new_rect = new_rect.translate(best.free.p0());

		auto split    = !(new_rect == best.free);
		auto old_free = best.free;

		already_placed.push_back(new_rect);
		to_be_placed.erase(
			remove(to_be_placed.begin(), to_be_placed.end(), best.to_place),
			to_be_placed.end());
		free_rectangles.erase(
			remove(free_rectangles.begin(), free_rectangles.end(), best.free),
			free_rectangles.end());

		if(split) {
			if(old_free.width() < old_free.height()) {
				Rectangle h1({new_rect.x0(), new_rect.y1()},
							 {old_free.x1(), old_free.y1()});
				Rectangle h2({new_rect.x1(), new_rect.y0()},
							 {old_free.x1(), new_rect.y1()});
				free_rectangles.push_back(h1);
				free_rectangles.push_back(h2);
			} else {
				Rectangle v1({new_rect.x0(), new_rect.y1()},
							 {new_rect.x1(), old_free.y1()});
				Rectangle v2({new_rect.x1(), new_rect.y0()},
							 {old_free.x1(), old_free.y1()});
				free_rectangles.push_back(v1);
				free_rectangles.push_back(v2);
			}
		}

		bool merged;

		do {
			merged = false;

		restart:
			for(int i = 0; i < free_rectangles.size(); i++) {
				for(int j = i + 1; j < free_rectangles.size(); j++) {
					auto a  = free_rectangles[i];
					auto b  = free_rectangles[j];
					auto un = rectangle_union(a, b);

					if(un.area() == a.area() + b.area()) {
						free_rectangles.erase(free_rectangles.begin() + i);
						free_rectangles.erase(free_rectangles.begin() + j);
						free_rectangles.push_back(un);

						merged = true;
						goto restart;
					}
				}
			}
		} while(merged);
	}

	assert(("did not place tree stand", did_place_stand));
	for(const auto & rect : already_placed) { assert(table.contains(rect)); }
	for(int i = 0; i < already_placed.size(); i++) {
		for(int j = i + 1; j < already_placed.size(); j++) {
			assert(rectangle_intersection(already_placed[i], already_placed[j])
				   .area() <= 0.0);
		}
    }
    cout << already_placed << endl;
}
