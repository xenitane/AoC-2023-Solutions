#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int num{}, k{};                                                                                                                                                                                                                                                                                                            \
	while (p + k < n && isdigit(str[p + k])) [[likely]] num = num * 10 + str[p + k++] - 48

struct game_data {
	int game_id;
	struct game_info {
		int red, green, blue;
	};
	std::vector<game_info> games;
};

void solve(const std::vector<game_data> &games) noexcept {
	int res1{}, res2{};
	for (const game_data &game : games) {
		bool				 f		= false;
		game_data::game_info gi_fin = {.red = 0, .green = 0, .blue = 0};
		for (const game_data::game_info &gi : game.games) {
			if (gi.red > 12 || gi.green > 13 || gi.blue > 14) f = true;
			gi_fin.red	 = std::max(gi_fin.red, gi.red);
			gi_fin.green = std::max(gi_fin.green, gi.green);
			gi_fin.blue	 = std::max(gi_fin.blue, gi.blue);
		}
		res1 += f ? 0 : game.game_id;
		res2 += gi_fin.red * gi_fin.green * gi_fin.blue;
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
				p += k - 1;
				games.push_back(game_data{.game_id = num, .games = std::vector<game_data::game_info>{}});
			}
			p++;
		}
		while (p < n) {
			games.back().games.push_back(game_data::game_info{0, 0, 0});
			while (p < n && line[p] ^ ';') {
				while (p < n && line[p] ^ ',' && line[p] ^ ';') {
					if (isdigit(line[p])) [[unlikely]] {
						extract_num(line, num, p, k, n);
						p += k;
						switch (line[p + 1]) {
						case 0x72: games.back().games.back().red = num; break;
						case 0x67: games.back().games.back().green = num; break;
						case 0x62: games.back().games.back().blue = num; break;
						}
					}
					p++;
				}
				if (line[p] == ',') p++;
			}
			p++;
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