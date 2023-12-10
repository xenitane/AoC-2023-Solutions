void get_seeds(std::vector<std::pair<long long, long long>> &sdvc) {
	std::string str;
	std::cin >> str;
	getline(std::cin, str);
	std::istringstream ss(str);
	for (long long seed, range; ss >> seed >> range;) sdvc.emplace_back(seed, range);
}
void consume_line() {
	std::string _1;
	getline(std::cin, _1);
}

std::vector<std::pair<long long, long long>> update_seeds(std::vector<std::pair<long long, long long>> &seeds, const std::map<long long, std::pair<long long, long long>> &mapping) {
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

std::vector<std::pair<long long, long long>> sort_and_merge(std::vector<std::pair<long long, long long>> &vec) {
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

// our solver function
void solve(int t) noexcept {
	while (t--) {
		// todo: write code here to solve the problem at hand
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
			mapping.emplace(LONG_LONG_MIN, std::make_pair(LONG_LONG_MIN, 0LL));
			mapping.emplace(LONG_LONG_MAX, std::make_pair(LONG_LONG_MAX, 0LL));
			seeds = update_seeds(seeds, mapping);
		}
		long long res = -1ULL ^ 1ULL << 63;
		seeds		  = sort_and_merge(seeds);
		while (!seeds.empty()) {
			res = std::min(res, seeds.back().first);
			seeds.pop_back();
		}
		std::cout << res << "\n";
	}
}
