#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

bool all_dots_row(const std::string &str) noexcept {
	for (char c : str)
		if (c) [[likely]]
			return false;
	return true;
}

using vi = std::vector<int>;

bool all_dots_col(const std::vector<std::string> &matrix, const size_t col, size_t n) noexcept {
	while (n--)
		if (matrix[n][col]) [[likely]]
			return false;
	return true;
}

long long all_pair_gal_dis(const vi &gpx, const vi &gpy, const vi &ecy, const vi &erx, const size_t num_galaxies, const long long expansion) noexcept {
	long long res{}, s_x{}, s_y{}, x, y;
	for (size_t i{}; i < num_galaxies;) {
		x = gpx[i] + expansion * erx[gpx[i]];
		y = gpy[i] + expansion * ecy[gpy[i]];
		s_x += x;
		s_y += y;
		res += ++i * (x + y) - (s_x + s_y);
	}
	return res;
}

void main_solver() noexcept {
	std::vector<std::string> matrix;
	for (std::string line; getline(std::cin, line);) {
		std::transform(line.begin(), line.end(), line.begin(), [](char c) noexcept -> char { return c == '#'; });
		matrix.push_back(line);
	}
	size_t n{matrix.size()}, m{matrix[0].size()}, num_gals{};
	vi	   empty_cols(m, 0);
	vi	   empty_rows(n, 0);
	empty_rows[0] = all_dots_row(matrix[0]);
	empty_cols[0] = all_dots_col(matrix, 0, n);
	for (size_t i{1}; i < n; i++) empty_rows[i] = empty_rows[i - 1] + all_dots_row(matrix[i]);
	for (size_t i{1}; i < m; i++) empty_cols[i] = empty_cols[i - 1] + all_dots_col(matrix, i, n);
	vi gal_pos_x(0);
	vi gal_pos_y(0);
	for (size_t i{}; i < n; i++)
		for (size_t j{}; j < m; j++)
			if (matrix[i][j]) [[unlikely]] {
				gal_pos_x.push_back(i);
				gal_pos_y.push_back(j);
				num_gals++;
			}
	std::sort(gal_pos_x.begin(), gal_pos_x.end());
	std::sort(gal_pos_y.begin(), gal_pos_y.end());
#define first_expansion	 1LL
#define second_expandion 999999LL

	std::cout << all_pair_gal_dis(gal_pos_x, gal_pos_y, empty_cols, empty_rows, num_gals, first_expansion) << '\n';
	std::cout << all_pair_gal_dis(gal_pos_x, gal_pos_y, empty_cols, empty_rows, num_gals, second_expandion) << '\n';

#undef first_expansion
#undef second_expandion
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input11.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}
