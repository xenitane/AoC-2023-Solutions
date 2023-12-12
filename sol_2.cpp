#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

struct game_data {
	int game_id;
	struct game_info {
		int red, green, blue;
	};
	std::vector<game_info> games;
};

void solve_part_1(const std::vector<game_data> &games) noexcept {
	int res{};
	for (const game_data &game : games) {
		bool f = false;
		for (const game_data::game_info &gi : game.games) {
			if (gi.red > 12 || gi.green > 13 || gi.blue > 14) f = true;
			if (f) break;
		}
		res += f ? 0 : game.game_id;
	}
	std::cout << res << "\n";
}

void solve_part_2(const std::vector<game_data> &games) noexcept {
	int res{};
	for (const game_data &game : games) {
		game_data::game_info gi_fin = {.red = 0, .green = 0, .blue = 0};
		for (const game_data::game_info &gi : game.games) {
			gi_fin.red	 = std::max(gi_fin.red, gi.red);
			gi_fin.green = std::max(gi_fin.green, gi.green);
			gi_fin.blue	 = std::max(gi_fin.blue, gi.blue);
		}
		res += gi_fin.red * gi_fin.green * gi_fin.blue;
	}
	std::cout << res << "\n";
}

void main_solver() noexcept {
	std::vector<game_data> games(0);
	for (std::string str; getline(std::cin, str);) {
		games.push_back(game_data{.game_id = std::stoi(str.substr(5, str.find(':') - 5)), .games = std::vector<game_data::game_info>(0)});
		std::istringstream iss(str.substr(str.find(':') + 1));
		size_t			   p = str.find(':') + 1;
		while (p != std::string::npos) {
			games.back().games.push_back(game_data::game_info{.red = 0, .green = 0, .blue = 0});
			size_t			   np = str.find(';', p);
			std::istringstream iss(str.substr(p, np == std::string::npos ? np : (np - p)));
			while (true) {
				int			qty;
				std::string color;
				iss >> qty >> color;
				switch (color[0]) {
				case 'r': games.back().games.back().red = qty; break;
				case 'g': games.back().games.back().green = qty; break;
				case 'b': games.back().games.back().blue = qty; break;
				}
				if (color.back() != ',') break;
			}
			p = np == std::string::npos ? np : (np + 1);
		}
	}
	solve_part_1(games);
	solve_part_2(games);
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