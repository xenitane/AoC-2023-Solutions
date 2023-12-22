#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

void transpose(std::vector<std::string> &matrix) {
	size_t n{matrix.size()}, m{matrix[0].size()};
	size_t mm{std::max(n, m)};
	matrix.resize(mm, std::string(mm, 0));
	for (std::string &row : matrix) row.resize(mm, 0);

	for (size_t i{}; i < mm; i++)
		for (size_t j{i + 1}; j < mm; j++) std::swap(matrix[i][j], matrix[j][i]);

	if (m < mm)
		while (m < mm--) matrix.pop_back();
	else
		while (n < mm--)
			for (std::string &row : matrix) row.pop_back();
}

int h_ref(const std::vector<std::string> &block, const size_t d = 0) noexcept {
	size_t n{block[0].size()};
	for (size_t i{1}; i < n; i++) {
		size_t k{std::min(i, n - i)};
		size_t df{};
		while (k--)
			for (const std::string &row : block) df += !!(row[i + k] ^ row[i - k - 1]);

		if (df == d) [[unlikely]]
			return i;
	}
	return 0;
}

void main_solver() noexcept {
	long long							  num_cols{}, num_rows{};
	long long							  num_cols1{}, num_rows1{};
	std::vector<std::vector<std::string>> blocks(1);
	for (std::string line; getline(std::cin, line);) {
		if (line.empty()) [[unlikely]]
			blocks.emplace_back(0);
		else {
			std::transform(line.begin(), line.end(), line.begin(), [](char c) noexcept -> char { return c == '#'; });
			blocks.back().push_back(line);
		}
	}
	while (!blocks.empty()) {
		num_cols += h_ref(blocks.back());
		num_cols1 += h_ref(blocks.back(), 1);
		transpose(blocks.back());
		num_rows += h_ref(blocks.back());
		num_rows1 += h_ref(blocks.back(), 1);
		blocks.pop_back();
	};
	std::cout << 100 * num_rows + num_cols << "\n" << 100 * num_rows1 + num_cols1 << "\n";
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input13.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}