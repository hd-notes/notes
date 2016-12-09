/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  sort_versions.cpp -- sort version numbers
  requires c++14
*/

#include "common.h"
#include "sort_versions.hpp"

const auto inline split(str s, char delim) noexcept {
    stringstream ss;
    vector<str>  elems;
    str          item;
    ss.str(s);

    while(getline(ss, item, delim)) { elems.push_back(item); }

    return elems;
}

const auto inline split_version(str version) noexcept {
    auto     split_version = split(version, '.');
    vec<i32> versions(split_version.size());

    transform(split_version.begin(), split_version.end(), versions.begin(),
              [](const str & s) { return stoi(s); });

    return versions;
}

const auto inline version_less(str v1, str v2) noexcept {
    auto s1 = split_version(v1);
    auto s2 = split_version(v2);

    return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
}

i32 main() {
    sort(versions.begin(), versions.end(), version_less);
    copy(versions.begin(), versions.end(), ostream_iterator<str>(cout, "\n"));
}
