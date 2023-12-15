#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	long long num{};                                                                                                                                                                                                                                                                                                           \
	while (p + k < n && isdigit(str[p + k])) num = num * 10 + str[p + k++] - 48

void solve(std::pair<std::vector<long long> *, std::vector<long long> *> seeds, std::pair<std::vector<std::pair<long long, long long>> *, std::vector<std::pair<long long, long long>> *> seed_ranges, const std::vector<std::map<long long, std::pair<long long, long long>>> &mappings) {
	for (const auto &map : mappings) {
		while (!seeds.first->empty()) {
			long long seed = seeds.first->back();
			auto	  itr  = std::prev(map.upper_bound(seed));
			if (itr->first + itr->second.second <= seed) seeds.second->push_back(seed);
			else seeds.second->push_back(seed + itr->second.first - itr->first);
			seeds.first->pop_back();
		}
		std::swap(seeds.first, seeds.second);

		while (!seed_ranges.first->empty()) {
			long long u{}, v{};
			std::tie(u, v) = seed_ranges.first->back();
			seed_ranges.first->pop_back();
			auto rtr = map.upper_bound(u);
			auto ltr = std::prev(rtr);
			if (u < ltr->first + ltr->second.second) {
				auto [a, b] = seed_ranges.second->emplace_back(ltr->second.first + u - ltr->first, std::min(v, ltr->second.second - u + ltr->first));
				if (v > b) seed_ranges.first->emplace_back(u + b, v - b);
			} else {
				auto [a, b] = seed_ranges.second->emplace_back(u, std::min(v, rtr->first - u));
				if (v > b) seed_ranges.first->emplace_back(rtr->first, v - b);
			}
		}
		std::sort(seed_ranges.second->begin(), seed_ranges.second->end());
		while (!seed_ranges.second->empty()) {
			auto [u, v] = seed_ranges.second->back();
			seed_ranges.second->pop_back();
			if (seed_ranges.second->empty() || u > seed_ranges.second->back().first + seed_ranges.second->back().second) seed_ranges.first->emplace_back(u, v);
			else seed_ranges.second->back().second = u + v - seed_ranges.second->back().first;
		}
	}
	long long res{LONG_LONG_MAX};
	for (long long &seed : *seeds.first) res = std::min(res, seed);
	std::cout << res << "\n";
	res = LONG_LONG_MAX;
	for (auto [seed, range] : *seed_ranges.first) res = std::min(res, seed);
	std::cout << res << "\n";
}

void main_solver() noexcept {
	std::vector<long long>										   *seeds = new std::vector<long long>(0), *seeds_o = new std::vector<long long>(0);
	std::vector<std::pair<long long, long long>>					 *seed_ranges = new std::vector<std::pair<long long, long long>>(0), *seed_ranges_o = new std::vector<std::pair<long long, long long>>(0);
	std::vector<std::map<long long, std::pair<long long, long long>>> mappings(0);
	std::string														  line;
	getline(std::cin, line);
	{
		bool   ns{};
		size_t p{}, n{line.size()};
		while (p < n) {
			if (isdigit(line[p])) {
				size_t k{};
				extract_num(line, num, p, k, n);
				seeds->push_back(num);
				if (ns) seed_ranges->back().second = num;
				else seed_ranges->emplace_back(num, 0);
				ns = !ns;
				p += k - 1;
			}
			p++;
		}
	}

	while (getline(std::cin, line)) {
		if (line.empty()) {
			mappings.push_back(std::map<long long, std::pair<long long, long long>>{});
			mappings.back().emplace(0xffffffffffffL, std::make_pair(0xffffffffffffL, 1LL));
			mappings.back().emplace(-0xffffffffffffL, std::make_pair(-0xffffffffffffL, 1LL));
		} else if (line.back() == 58) continue;
		else {
			size_t p{}, n{line.size()}, k{};
			extract_num(line, to, p, k, n);
			k++;
			extract_num(line, from, p, k, n);
			k++;
			extract_num(line, range, p, k, n);
			mappings.back()[from] = std::make_pair(to, range);
		}
	}
	solve(std::make_pair(seeds, seeds_o), std::make_pair(seed_ranges, seed_ranges_o), mappings);
	delete seeds;
	delete seed_ranges;
	delete seeds_o;
	delete seed_ranges_o;
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