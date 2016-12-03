/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  format_numbers.cpp -- formatting of tables and doubles
*/

#include "format_numbers.hpp"
#include "common.h"

namespace ipi {
	const inline auto round(f64 d, i32 digits) noexcept {
		auto offset = pow(10, digits);
		d *= offset;
		d = (f64)((i64)(d + 0.5));
		return d / offset;
	}

	const inline auto vec_to_int(const vec<f64> v) noexcept {
		vec<i32> ret(v.size());

		// dont use default constructor for the elements
		ret.resize(v.size());
		std::transform(v.begin(), v.end(), ret.begin(),
					   [](f64 d) { return (i32)round(d, 0); });
		return ret;
	}

	const inline auto vec_rounded(vec<f64> v) noexcept {
		std::transform(v.begin(), v.end(), v.begin(), std::bind(round, _1, 2));
		return v;
	}

	const inline auto double_to_string(f64 x) noexcept {
		x        = round(x, 2);
		auto tmp = to_string(x);
		auto dot = tmp.rfind('.');
		str  lhs = tmp.substr(0, dot);
		str  rhs = tmp.substr(dot, tmp.size() - dot);
		rhs.resize(16);

		while(rhs.size() < 3) rhs += "0";
		rhs = rhs.substr(0, 3);

		for(i32 i = 3; i < lhs.size(); i += 4) {
			lhs.insert(lhs.end() - i, '\'');
		}

		return lhs + rhs;
	}

	vec<str> format_numbers(vec<f64> v) {}
}

using namespace ipi;

i32 main() { std::cout << double_to_string(1000000) << std::endl; }
