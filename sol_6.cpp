#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

long long solve(long long a, long long b) noexcept {
	double det = sqrtf64(a * a - 4 * b);

	long long rl = ceil((a - det) / 2);
	if (rl * (a - rl) == b) [[unlikely]]
		rl += 1;

	long long rr = floor((a + det) / 2);
	if (rr * (a - rr) == b) [[unlikely]]
		rr -= 1;

	return rr - rl + 1;
}

void get_data_from_line(std::vector<int> &numbers, long long &number) noexcept {
	std::string line;
	getline(std::cin, line);

	size_t p{line.find(':') + 1}, n{line.size()};

	while (p < n) {
		if (isdigit(line[p])) {
			number		   = number * 10 + line[p] - 48;
			numbers.back() = numbers.back() * 10 + line[p] - 48;
		} else if (numbers.empty() || numbers.back()) numbers.push_back(0);
		p++;
	}
}

void main_solver() noexcept {
	std::vector<int> times;
	std::vector<int> distances;
	long long		 time{};
	long long		 distance{};

	get_data_from_line(times, time);
	get_data_from_line(distances, distance);

	long long res{1};
	while (!times.empty()) {
		res *= solve(times.back(), distances.back());
		times.pop_back();
		distances.pop_back();
	}
	std::cout << res << '\n' << solve(time, distance) << '\n';
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input6.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}