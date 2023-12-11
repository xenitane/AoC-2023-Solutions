void get_seeds(std::vector<long long> &sdvc) noexcept {
	std::string str;
	std::cin >> str;
	getline(std::cin, str);
	std::istringstream ss(str);
	for (long long seed; ss >> seed;) sdvc.push_back(seed);
}
void consume_line() noexcept {
	std::string _1;
	getline(std::cin, _1);
}

void update_seeds(std::vector<long long> &seeds, const std::map<long long, std::pair<long long, long long>> &mapping) noexcept {
	for (long long &seed : seeds) {
		if (seed < mapping.begin()->first) continue;
		auto zzz = std::prev(mapping.upper_bound(seed));
		if (zzz->first + zzz->second.second <= seed) continue;
		seed += zzz->second.first - zzz->first;
	}
}

void solve() noexcept {
	std::vector<long long> seeds(0);
	get_seeds(seeds);
	consume_line();
	for (int i = 0; i < 7; i++) {
		consume_line();
		std::map<long long, std::pair<long long, long long>> mapping;
		for (std::string line; getline(std::cin, line);) {
			if (line.empty()) break;
			std::istringstream iss(line);
			long long		   from, to, range;
			iss >> to >> from >> range;
			mapping.emplace(from, std::make_pair(to, range));
		}
		update_seeds(seeds, mapping);
	}
	long long res = std::numeric_limits<long long>::max();
	while (!seeds.empty()) {
		res = std::min(res, seeds.back());
		seeds.pop_back();
	}
	std::cout << res << "\n";
}