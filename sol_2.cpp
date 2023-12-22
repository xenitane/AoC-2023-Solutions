#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int num{}, k{};                                                                                                                                                                                                                                                                                                            \
	while (p + k < n && isdigit(str[p + k])) [[likely]] num = num * 10 + str[p + k++] - 48;                                                                                                                                                                                                                                    \
	p += k - 1

struct game_data {
	int game_id;
	struct game_info {
		int red;
		int green;
		int blue;
	};
	std::vector<game_info> games;
};

void solve(const std::vector<game_data> &games) noexcept {
	int res1{}, res2{};
	for (const game_data &game : games) {
		bool f = false;
		int	 fr{}, fg{}, fb{};

		for (const game_data::game_info &gi : game.games) {
			auto [cr, cg, cb] = gi;
			if (cr > 12 || cg > 13 || cb > 14) f = true;
			fr = std::max(fr, cr);
			fg = std::max(fg, cg);
			fb = std::max(fb, cb);
		}
		res1 += f ? 0 : game.game_id;
		res2 += fr * fg * fb;
	}
	std::cout << res1 << '\n' << res2 << '\n';
}

void main_solver() noexcept {
	std::vector<game_data> games(0);
	for (std::string line; getline(std::cin, line);) {
		size_t p{}, n{line.size()};
		while (p < n && line[p] ^ ':') {
			if (isdigit(line[p])) [[unlikely]] {
				extract_num(line, num, p, k, n);
				games.push_back(game_data{.game_id = num, .games = std::vector<game_data::game_info>{}});
			}
			p++;
		}
		while (p < n) {
			int r{}, g{}, b{};
			while (p < n && line[p] ^ ';') {
				while (p < n && line[p] ^ ',' && line[p] ^ ';') {
					if (isdigit(line[p])) [[unlikely]] {
						extract_num(line, num, p, k, n);
						switch (line[p + 2]) {
						case 'r': r = num; break;
						case 'g': g = num; break;
						case 'b': b = num; break;
						}
					}
					p++;
				}
				if (line[p] == ',') p++;
			}
			p++;
			games.back().games.push_back(game_data::game_info{r, g, b});
		}
	}
	solve(games);
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input2.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);

	main_solver();

	return 0;
}