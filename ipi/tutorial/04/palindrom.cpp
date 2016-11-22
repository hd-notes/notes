/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  palindrom.cpp -- test if a string is a palindrome
*/

#include "common.h"

str to_lower(str s) {
	str ret;

	for(const auto & c : s) ret += std::tolower(c);

	return ret;
}

str letters_only(str s) {
	str ret;

	for(const auto & c : s) {
		if(std::isalpha(c)) ret += c;
	}

	return ret;
}

bool is_palindrom(str s) {
	s = letters_only(to_lower(s));

	i32 j = s.size() - 1;
	for(i32 i = 0; i < j; i++) {
		if(s[i] != s[j]) return false;

		j--;
	}

	return true;
}

int main() {
	assert(is_palindrom("Otto"));
	assert(is_palindrom("Anna"));
	assert(is_palindrom("Rentner"));
	assert(is_palindrom("Lagerregal"));
	assert(is_palindrom("Ein Neger mit Gazelle zagt im Regen nie"));
	assert(!is_palindrom("Ein Neger mit Gazelle zagt im Regen immer"));
	assert(!is_palindrom("Neger mit Gazelle zagt im Regen immer"));

	str s;

	while(1) {
		std::cout << "to check: " << std::endl;
		std::getline(std::cin, s);
		std::cout << (is_palindrom(s) ? "ist ein Palindrom"
									  : "ist kein Palindrom")
				  << std::endl;
	}
}
