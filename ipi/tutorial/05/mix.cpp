/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  mix.cpp -- mixing up the letters in words
*/

#include "common.h"
#include "text.hpp"

vec<str> const inline split_words(str s) noexcept {
	std::istringstream iss(s);
	return {std::istream_iterator<str>{iss}, std::istream_iterator<str>{}};
}

auto mix(str s) noexcept {
	auto begin = std::find_if(s.begin(), s.end(),
							  [](char s) { return std::isalpha(s); }) + 1;

	auto end =
		std::find_if(std::reverse_iterator<str::iterator>(s.begin()),
					 std::reverse_iterator<str::iterator>(s.end()),
					 [](char s) { return std::isalpha(s); })
			.base() - 1;

	std::random_shuffle(begin, end);

	return s;
}

auto split_and_mix(str s) noexcept {}

int main() {
	std::cout << split_words(str1) << std::endl;
	std::cout << mix(split_words(str1)[0]) << std::endl;
}
