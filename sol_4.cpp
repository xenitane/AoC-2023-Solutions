#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int num{}, k{};                                                                                                                                                                                                                                                                                                            \
	while (p + k < n && isdigit(str[p + k])) num = num * 10 + str[p + k++] - 48

struct card_info {
	int						id;
	std::unordered_set<int> present;
	std::unordered_set<int> needed;
};

void solve(const std::vector<card_info> &cards) {
	int				 res1{}, res2{};
	std::vector<int> qty(cards.size(), 1);
	for (const card_info &card : cards) {
		int cc{};
		for (const int &p : card.present)
			if (card.needed.contains(p)) {
				qty[cc + card.id] += qty[card.id - 1];
				cc++;
			}
		res1 += (1 << cc) / 2;
		res2 += qty[card.id - 1];
	}
	std::cout << res1 << '\12' << res2 << '\12';
}

void main_solver() noexcept {
	std::vector<card_info> cards{};
	for (std::string line; getline(std::cin, line);) {
		size_t p{0}, n{line.size()};
		while (p < n && line[p] ^ 58) {
			if (isdigit(line[p])) {
				extract_num(line, num, p, k, n);
				cards.push_back(card_info{.id = num, .present = std::unordered_set<int>{}, .needed = std::unordered_set<int>{}});
				p += k - 1;
			}
			p++;
		}
		while (line[p] ^ 124) {
			if (isdigit(line[p])) {
				extract_num(line, num, p, k, n);
				cards.back().present.insert(num);
				p += k - 1;
			}
			p++;
		}
		while (p < n) {
			if (isdigit(line[p])) {
				extract_num(line, num, p, k, n);
				cards.back().needed.insert(num);
				p += k - 1;
			}
			p++;
		}
	}
	solve(cards);
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);

	main_solver();

	return 0;
}