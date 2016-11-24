/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  perfect_shuffle.cpp -- Implementation of perfect suffle
*/

#include "common.h"

auto const inline init_deck() noexcept {
	vec<int> cards(52);
	std::iota(cards.begin(), cards.end(), 0);

	return cards;
}

auto const inline check_deck(vec<int> cards) noexcept {
	auto correct_deck = init_deck();

	return correct_deck == cards;
}

auto const inline shuffle(vec<int> cards, bool out) noexcept {
	vec<int> halves[2];
	vec<int> shuffeled;

	halves[0].reserve(26);
	halves[1].reserve(26);
	shuffeled.reserve(52);

	std::copy(cards.begin(), cards.begin() + 26, halves[1].begin());
	std::copy(cards.begin() + 26, cards.end(), halves[0].begin());

	out %= 2;

	for(i32 i = 0; i < 52; i++) {
		shuffeled.push_back(halves[(i + out) % 2][i / 2]);
	}

	return shuffeled;
}

i32 main() {
	auto cards = init_deck();
	assert(check_deck(cards));

	i32 iterations = 0;

	do {
		cards = shuffle(cards, false);
		iterations++;
	} while(!check_deck(cards));

	std::cout << "Perfect-In-Shuffle: " << iterations << " iterations"
			  << std::endl;

	iterations = 0;

	do {
		cards = shuffle(cards, true);
		iterations++;
	} while(!check_deck(cards));

	std::cout << "Perfect-Out-Shuffle: " << iterations << " iterations"
			  << std::endl;
}
