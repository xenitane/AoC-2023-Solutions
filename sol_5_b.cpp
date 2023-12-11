#include <bits/stdc++.h>
void get_seeds(std::vector<std::pair<long long, long long>> &sdvc) noexcept {
	std::string str;
	std::cin >> str;
	getline(std::cin, str);
	std::istringstream ss(str);
	for (long long seed, range; ss >> seed >> range;) sdvc.emplace_back(seed, range);
}
void consume_line() noexcept {
	std::string _1;
	getline(std::cin, _1);
}

std::vector<std::pair<long long, long long>> update_seeds(std::vector<std::pair<long long, long long>> &seeds, const std::map<long long, std::pair<long long, long long>> &mapping) noexcept {
	std::vector<std::pair<long long, long long>> res(0);
	while (!seeds.empty()) {
		long long u, v;
		std::tie(u, v) = seeds.back();
		seeds.pop_back();

		if (u >= mapping.rbegin()->first + mapping.rbegin()->second.second || u + v <= mapping.begin()->first) res.emplace_back(u, v);
		else {
			auto zzz = mapping.upper_bound(u);
			auto zzy = std::prev(zzz);
			if (u < zzy->first + zzy->second.second) {
				auto [a, b] = res.emplace_back(u - zzy->first + zzy->second.first, std::min(v, zzy->second.second - u + zzy->first));
				if (v > b) seeds.emplace_back(u + b, v - b);
			} else {
				auto [a, b] = res.emplace_back(u, std::min(v, zzz->first - u));
				if (v > b) seeds.emplace_back(zzz->first, v - b);
			}
		}
	}
	return res;
}

std::vector<std::pair<long long, long long>> sort_and_merge(std::vector<std::pair<long long, long long>> &vec) noexcept {
	std::vector<std::pair<long long, long long>> res(0);
	std::sort(vec.rbegin(), vec.rend());
	res.push_back(vec.back());
	vec.pop_back();
	while (!vec.empty()) {
		auto [u, v] = vec.back();
		vec.pop_back();
		if (u > res.back().first + res.back().second) res.emplace_back(u, v);
		else res.back().second = u + v - res.back().first;
	}
	return res;
}

void solve() noexcept {
	std::vector<std::pair<long long, long long>> seeds(0);
	get_seeds(seeds);
	consume_line();
	for (int i = 0; i < 7; i++) {
		seeds = sort_and_merge(seeds);
		consume_line();
		std::map<long long, std::pair<long long, long long>> mapping;
		for (std::string line; getline(std::cin, line);) {
			if (line.empty()) break;
			std::istringstream iss(line);
			long long		   from, to, range;
			iss >> to >> from >> range;
			mapping.emplace(from, std::make_pair(to, range));
		}
		mapping.emplace(0xffffffffffff, std::make_pair(0xffffffffffff, 1LL));
		mapping.emplace(-0xffffffffffff, std::make_pair(-0xffffffffffff, 1LL));
		seeds = update_seeds(seeds, mapping);
	}
	long long res = 0x7fffffffffffffff;
	seeds		  = sort_and_merge(seeds);
	while (!seeds.empty()) {
		res = std::min(res, seeds.back().first);
		seeds.pop_back();
	}
	std::cout << res << "\n";
}
