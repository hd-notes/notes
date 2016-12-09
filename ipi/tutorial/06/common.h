/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  common.h -- Common defines and includes
*/

#ifndef _COMMON_H
#define _COMMON_H

#include <algorithm>
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using f64 = double;

using str = std::string;
using namespace std;
using namespace std::placeholders;

template <typename T>
using vec = std::vector<T>;

template <typename T>
std::ostream & operator<<(std::ostream & out, const std::vector<T> & v) {
    if(!v.empty()) {
        out << '[';
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

template <typename T, u32 size>
auto to_vec(T (&data)[size]) {
    vec<T> vector;
    vector.assign(data, data + size);
    return vector;
}

template <typename T, typename G>
std::ostream & operator<<(std::ostream & out, const std::map<T, G> & m) {
    T key;
    G value;

    out << '[';
    for(const auto & key_value : m) {
        tie(key, value) = key_value;

        out << "{" << key << " : " << value << "}, ";
    }

    if(!m.empty()) { out << "\b\b"; }
    out << ']';

    return out;
}

#endif
