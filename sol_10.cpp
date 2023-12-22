#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

using tube = std::bitset<4>;

void bfs(std::vector<std::vector<tube>> &matrix, size_t x, size_t y, const int n, const int m) noexcept {
	std::deque<std::pair<int, int>> dq;
	dq.emplace_back(x, y);
	while (!dq.empty()) {
		auto [u, v] = dq.front();
		dq.pop_front();
		if (u < 0 || v < 0 || u == n || v == m || matrix[u][v].test(0)) [[likely]]
			continue;

		matrix[u][v] = 1;
		dq.emplace_back(u - 1, v - 1);
		dq.emplace_back(u - 1, v);
		dq.emplace_back(u - 1, v + 1);
		dq.emplace_back(u, v - 1);
		dq.emplace_back(u, v + 1);
		dq.emplace_back(u + 1, v - 1);
		dq.emplace_back(u + 1, v);
		dq.emplace_back(u + 1, v + 1);
	}
}

enum move_name { RIGHT, LEFT, UP, DOWN };

void main_solver() noexcept {
	std::vector<std::vector<tube>> matrix;
	size_t						   start_x{}, start_y{};
	for (std::string line; getline(std::cin, line);) {
		matrix.emplace_back(0);
		for (char c : line) {
			matrix.back().emplace_back(0);
			if (c == 'S') [[unlikely]] {
				start_x = matrix.size() - 1;
				start_y = matrix.back().size() - 1;
			} else {
				if (c == '-' || c == 'L' || c == 'F') matrix.back().back().set(RIGHT);
				if (c == '-' || c == 'J' || c == '7') matrix.back().back().set(LEFT);
				if (c == '|' || c == 'L' || c == 'J') matrix.back().back().set(UP);
				if (c == '|' || c == 'F' || c == '7') matrix.back().back().set(DOWN);
			}
			matrix.back().emplace_back(0);
		}
		matrix.back().pop_back();
		matrix.emplace_back(matrix.back().size(), 0);
	}
	matrix.pop_back();
	size_t n{matrix.size()}, m{matrix[0].size()};

	if (start_y > 0 && matrix[start_x][start_y - 2].test(RIGHT)) matrix[start_x][start_y].set(LEFT);
	if (start_y < m - 1 && matrix[start_x][start_y + 2].test(LEFT)) matrix[start_x][start_y].set(RIGHT);
	if (start_x < n - 1 && matrix[start_x + 2][start_y].test(UP)) matrix[start_x][start_y].set(DOWN);
	if (start_x > 0 && matrix[start_x - 2][start_y].test(DOWN)) matrix[start_x][start_y].set(UP);
	int									  res{-1};
	std::deque<std::pair<size_t, size_t>> dq;
	dq.emplace_back(start_x, start_y);

	std::vector<std::vector<bool>> vis(n, std::vector<bool>(m, false));

	while (!dq.empty()) {
		size_t num{dq.size()};
		bool   f{};
		while (num--) {
			auto [u, v] = dq.front();
			dq.pop_front();
			if (vis[u][v]) continue;
			f		  = true;
			vis[u][v] = true;
			if (matrix[u][v].test(RIGHT) && v < m - 2) {
				dq.emplace_back(u, v + 2);
				matrix[u][v + 1] = 15;
			}
			if (matrix[u][v].test(LEFT) && v > 0) {
				dq.emplace_back(u, v - 2);
				matrix[u][v - 1] = 15;
			}
			if (matrix[u][v].test(UP) && u > 0) {
				dq.emplace_back(u - 2, v);
				matrix[u - 1][v] = 15;
			}
			if (matrix[u][v].test(DOWN) && u < n - 2) {
				dq.emplace_back(u + 2, v);
				matrix[u + 1][v] = 15;
			}
			matrix[u][v] = 15;
		}
		res += f;
	}
	std::cout << res << '\n';
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < m; j++) matrix[i][j] = matrix[i][j].all() ? 1 : 0;

	res = 0;
	for (size_t i{}; i < m; i++) {
		bfs(matrix, 0, i, n, m);
		bfs(matrix, n - 1, i, n, m);
	}
	for (size_t i{}; i < n; i++) {
		bfs(matrix, i, 0, n, m);
		bfs(matrix, i, m - 1, n, m);
	}
	for (size_t i{}; i < n; i += 2)
		for (size_t j{}; j < m; j += 2) res += !matrix[i][j].test(0);

	std::cout << res << '\n';
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input10.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}
