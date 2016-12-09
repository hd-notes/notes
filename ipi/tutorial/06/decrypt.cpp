/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  decrypt.cpp -- decrypt text using character probabilities
  requires c++14
*/

#include "common.h"

auto read_whole_file(str filename) {
    ifstream file(filename);
    str      contents;

    // reserve enough space in the buffer string
    file.seekg(0, ios::end);
    contents.reserve(file.tellg());
    file.seekg(0, ios::beg);

    // read the whole file to memory
    contents.assign(istreambuf_iterator<char>(file),
                    istreambuf_iterator<char>());

    file.close();

    return contents;
}

template <typename A, typename B>
const pair<B, A> flip_pair(const pair<A, B> & p) noexcept {
    return pair<B, A>(p.second, p.first);
}

template <typename A, typename B>
const map<B, A> flip_map(const map<A, B> & src) noexcept {
    map<B, A> dst;
    transform(src.begin(), src.end(), inserter(dst, dst.begin()),
              flip_pair<A, B>);
    return dst;
}

i32 main() {
	auto text = read_whole_file("encrypted_text.txt");

	// std::map<char, int> c;

	// for (auto iter = text.begin(); iter != text.end(); ++iter) {
	// 	if(std::isalpha(*iter)) {
	// 		*iter = std::tolower(*iter);
	// 		c[*iter] += 1;
	// 	}
	// }

	// cout << c << endl;

    vec<i32> cnts(128);
    for_each(text.begin(), text.end(), [&](char c) {
        if(isalpha(c)) cnts[(unsigned char)tolower(c)]++;
    });

    map<char, int> counts;
    for(u32 i = 0; i < cnts.size(); i++) {
        if(cnts[i] > 0) { counts[i] = cnts[i]; }
	}

	// cout << counts << endl;

    auto sorted = flip_map(counts);

    vec<char> letters = {
        'z', 'j', 'q', 'x', 'k', 'v', 'b', 'y', 'g', 'p', 'w', 'f', 'm',
        'c', 'u', 'l', 'd', 'r', 'h', 's', 'n', 'i', 'o', 'a', 't', 'e',
    };

    map<char, char> decrypt;

    i32  key, counter = 0;
    char value;
    for(const auto & key_value : sorted) {
        tie(key, value) = key_value;

        decrypt[value]          = letters[counter];
        decrypt[toupper(value)] = toupper(letters[counter]);

        counter++;
    }

    transform(text.begin(), text.end(), text.begin(), [&](char c) {
        if(isalpha(c)) {
            return decrypt[c];
        } else {
            return c;
        }
    });

    ofstream out("decrypted_text.txt");
    out << text;
    out.close();
}
