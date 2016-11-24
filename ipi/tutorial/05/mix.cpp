/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  mix.cpp -- mixing up the letters in words
  Uses c++14
*/

#include "common.h"
#include "text.hpp"

vec<str> const inline split_words(str s) noexcept {
	std::istringstream iss(s);
	return {std::istream_iterator<str>{iss}, std::istream_iterator<str>{}};
}

auto mix(str s) noexcept {
	auto begin = std::find_if(s.begin(), s.end(),
							  [](char s) { return std::isalpha(s); }) +
				 1;

    auto end = std::find_if(std::reverse_iterator<str::iterator>(s.end()),
							std::reverse_iterator<str::iterator>(s.begin()),
							[](char s) { return std::isalpha(s); })
				   .base() -
			   1;

	std::random_shuffle(begin, end);

	return s;
}

auto concat(vec<str> strs, const char * delim = " ") {
	switch(strs.size()) {
	case 0:
		return str("");
	case 1:
		return strs[0];
	default:
		std::ostringstream os;
		std::copy(strs.begin(), strs.end() - 1,
				  std::ostream_iterator<str>(os, delim));
		os << *strs.rbegin();
		return os.str();
	}
}

auto split_and_mix(str s) noexcept {
	auto words = split_words(s);

	std::transform(words.begin(), words.end(), words.begin(), mix);

	return concat(words);
}

int main() {
	for(const auto & str : {str1, str2, str3, str4, str5}) {
		std::cout << str << std::endl;
		std::cout << split_and_mix(str) << std::endl;
	}
}
