#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int num{}, k{};                                                                                                                                                                                                                                                                                                            \
	while (p + k < n && isdigit(str[p + k])) num = num * 10 + str[p + k++] - 48

void solve(const std::unordered_map<char, std::unordered_set<int>> &special_chars, const std::unordered_multimap<int, std::tuple<int, int, int>> &number_pos_len, const int rows, const int cols) {
	int											 res{};
	std::unordered_map<size_t, std::vector<int>> star_data;
	for (const auto &[num, pos_len] : number_pos_len) {
		int i{}, j{}, k{};
		std::tie(i, j, k) = pos_len;

		int u = std::max(0, i - 1);
		int d = std::min(rows, i + 2);

		int l = std::max(0, j - 1);
		int r = std::min(cols, j + k + 1);

		bool needed{};
		for (i = u; i < d; i++)
			for (j = l; j < r; j++)
				for (const auto &[sc, poss] : special_chars)
					if (poss.contains(i * cols + j)) {
						needed = true;
						if (sc == 42) star_data[i * cols + j].push_back(num);
					}

		res += needed ? num : 0;
	}
	std::cout << res << '\12';
	res = 0;
	for (const auto &[p, nums] : star_data)
		if (nums.size() == 2) res += nums[0] * nums[1];
	std::cout << res << '\12';
}

void main_solver() noexcept {
	std::unordered_map<char, std::unordered_set<int>>		special_chars;
	std::unordered_multimap<int, std::tuple<int, int, int>> number_pos_len;
	int														rows{}, cols{};
	for (std::string line; getline(std::cin, line);) {
		cols = line.length();
		for (int i{}; i < cols; i++) {
			if (isdigit(line[i])) {
				extract_num(line, num, i, k, cols);
				number_pos_len.emplace(num, std::make_tuple(rows, i, k));
				i += k - 1;
			} else if (line[i] ^ 46) special_chars[line[i]].emplace(rows * cols + i);
		}
		rows++;
	}
	solve(special_chars, number_pos_len, rows, cols);
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