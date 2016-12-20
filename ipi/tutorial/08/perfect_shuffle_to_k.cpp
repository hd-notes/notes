/*
  Copyright (C) 2016 by Robin Heinemann. All Rights Reserved.
  perfect_shuffle_to_k.cpp -- perfect shuffle to position k
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

	if(out)
		out = 1;
	else
		out = 0;

	for(i32 i = 0; i < 52; i++) {
		shuffeled.push_back(halves[(i + out) % 2][i / 2]);
	}

	return shuffeled;
}

auto shuffle_top_to(vec<int> deck, uint8_t k) noexcept {
	if(k != 0) {
		for(i32 i = log2(k); i >= 0; i--) {
			deck = shuffle(deck, ~(k >> i) & 1);
		}
	}
	return deck;
}

i32 main() {
	for(i32 i = 0; i < 52; i++) {
		auto cards = init_deck();
		cards      = shuffle_top_to(cards, i);
		assert(cards[i] == 0);
	}
}
