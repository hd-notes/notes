/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  ordered_insert.cpp -- Insert ints read from cmdline ordered into a vector
  Uses c++14
*/

#include "common.h"

template <typename T>
auto const inline ordered_insert(vec<T> & v, const T & n) noexcept {
	v.insert(std::find_if(v.begin(), v.end(),
						  [=](const T & other) { return other > n; }),
			 n);
}

i32 main() {
    i32      user_input;
    vec<i32> numbers;

    while(true) {
        user_input = -1;
        std::cin >> user_input;

        // check for valid number
        if(!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n'); // skip bad input
            continue;
        }

        if(user_input < 0) {
            break;
        } else {
            ordered_insert(numbers, user_input);
        }

        std::cout << numbers << std::endl;
    }
}
