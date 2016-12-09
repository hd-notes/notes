/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  format_numbers.cpp -- formatting of tables and doubles
  requires c++14
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

        ret.resize(v.size());
        transform(v.begin(), v.end(), ret.begin(),
                  [](f64 d) { return (i32)round(d, 0); });
        return ret;
    }

    const inline auto vec_rounded(vec<f64> v) noexcept {
        transform(v.begin(), v.end(), v.begin(), bind(round, _1, 2));
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

        for(u32 i = 3; i < lhs.size(); i += 4) {
            if(isdigit(lhs[lhs.size() - i - 1])) {
                lhs.insert(lhs.end() - i, '\'');
            }
        }

        return str(16 - lhs.size() - rhs.size(), ' ') + lhs + rhs;
    }

    const inline auto format_numbers(vec<f64> v) noexcept {
        vec<str> formatted_numbers;
        formatted_numbers.resize(v.size());
        transform(v.begin(), v.end(), formatted_numbers.begin(),
                  double_to_string);
        return formatted_numbers;
    }
}

using namespace ipi;

i32 main() {
    const auto nums = format_numbers(numbers);
    copy(nums.begin(), nums.end(), ostream_iterator<str>(cout, "\n"));
}
