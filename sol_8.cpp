#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

long long gcd(long long a, long long b) noexcept {
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

int get_distance(int start, const std::unordered_map<int, std::unique_ptr<int>> &targets, const std::vector<bool> &steps) noexcept {
	size_t p{1}, n{steps.size()};
	start = targets.at(start).get()[steps[0]];
	while ((start & 0xff) ^ 25) start = targets.at(start).get()[steps[p++ % n]];
	return p;
}

void main_solver() noexcept {
	std::vector<bool> steps;
	{
		std::string line;
		getline(std::cin, line);
		for (char c : line) steps.push_back(c ^ 'L');
		getline(std::cin, line);
	}

	std::map<int, int>							  starts;
	std::unordered_map<int, std::unique_ptr<int>> targets;

	for (std::string target; getline(std::cin, target);) {
		int from{((target[0] - 'A') << 16) | ((target[1] - 'A') << 8) | ((target[2] - 'A'))};
		int left_to{((target[7] - 'A') << 16) | ((target[8] - 'A') << 8) | ((target[9] - 'A'))};
		int right_to{((target[12] - 'A') << 16) | ((target[13] - 'A') << 8) | ((target[14] - 'A'))};

		if (!(from & 0xff)) [[unlikely]]
			starts.emplace(from, 0);
		targets.emplace(from, new int[2]{left_to, right_to});
	}

	for (auto ftr = starts.begin(); ftr != starts.end(); ftr++) ftr->second = get_distance(ftr->first, targets, steps);

	std::cout << starts[0] << '\n';
	long long res{1};
	for (auto &[a, b] : starts) res = res * b / gcd(res, b);
	std::cout << res << '\n';
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input8.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}