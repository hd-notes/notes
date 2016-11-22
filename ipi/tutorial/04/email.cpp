/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  email.cpp -- check if a string is a email
*/

#include "common.h"
#include <regex>


// Benutzung von regex ist mit Dr. Köthe abgesprochen
bool is_email(str s) {
	std::regex email_regex("[\\w.-]+@[\\w.-]+\\.[\\w-]+");
	return std::regex_match(s, email_regex);
}

i32 main() {
	assert(is_email("a@a.a"));
	assert(is_email("a.a@a.a.a"));
	assert(is_email("a.aa.a@a.a.a.a.de"));
	assert(is_email("aaaa@a.aaade"));
	assert(is_email("ab.ac_a-aa@a.aa.ade-"));
	assert(is_email("ab.ac_a-aa@a.aa.ade_"));

	assert(!is_email("a@a.a."));
	assert(!is_email("a.aa.a.a"));
	assert(!is_email("a.aa.a@aaaade"));
	assert(!is_email("a@aaa@a.aaade"));
	assert(!is_email("ab.ac*a-aa@a.aa.ade-"));
	assert(!is_email("ab.ac_a-aa@a.aa.ade_."));
}
