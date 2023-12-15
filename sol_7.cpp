#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

int card_denom(char c) noexcept {
	if (isdigit(c)) [[likely]]
		return c - 48;
	switch (c) {
	case 'T': return 10;
	case 'J': return 11;
	case 'Q': return 12;
	case 'K': return 13;
	case 'A': return 14;
	}
	return 1;
}

int frq[15]{};

std::tuple<int, int, int> make_card(const std::string &line) noexcept {
	int card_num{}, bet{}, rank{}, den{};
	for (int &i : frq) i = 0;
	size_t p{}, n{line.size()};
	while (line[p] ^ ' ') {
		den		 = card_denom(line[p]);
		card_num = (card_num << 4) | den;
		frq[den]++;
		p++;
	}
	while (p < n) {
		if (isdigit(line[p])) [[likely]]
			bet = bet * 10 + line[p] - 48;
		p++;
	}

	std::sort(frq, frq + 15);
	if (frq[14] == 5) rank = 6;
	else if (frq[14] == 4) rank = 5;
	else if (frq[14] == 3) rank = frq[13] == 2 ? 4 : 3;
	else if (frq[14] == 2) rank = frq[13] == 2 ? 2 : 1;

	return std::make_tuple(rank, card_num, bet);
}

void modify_cards(std::vector<std::tuple<int, int, int>> &cards) noexcept {
	for (auto &[rank, card, bet] : cards) {
		for (int &i : frq) i = 0;
		int i{20};

		while (i) {
			i -= 4;
			if (((card >> i) & 15) == 11) [[unlikely]]
				card ^= (10 << i);
			frq[(card >> i) & 15]++;
		}
		if (!frq[1]) [[likely]]
			continue;

		std::sort(frq + 2, frq + 15);
		frq[14] += frq[1];
		if (frq[14] == 5) rank = 6;
		else if (frq[14] == 4) rank = 5;
		else if (frq[14] == 3) rank = frq[13] == 2 ? 4 : 3;
		else if (frq[14] == 2) rank = frq[13] == 2 ? 2 : 1;
	}
}

void main_solver() noexcept {
	std::vector<std::tuple<int, int, int>> cards(0);
	size_t								   n{};
	long long							   res{};
	for (std::string line; getline(std::cin, line); n++) cards.push_back(make_card(line));

	std::sort(cards.begin(), cards.end());
	for (size_t i{}; i < n; i++) res += (i + 1) * std::get<2>(cards[i]);
	std::cout << res << '\n';

	res = 0;
	modify_cards(cards);
	std::sort(cards.begin(), cards.end());
	for (size_t i{}; i < n; i++) res += (i + 1) * std::get<2>(cards[i]);
	std::cout << res << '\n';
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input7.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}