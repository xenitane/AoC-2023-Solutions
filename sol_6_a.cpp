void read_line(std::vector<int> &vec) {
	std::string str;
	std::cin >> str;
	getline(std::cin, str);
	std::istringstream ss(str);
	for (int num; ss >> num;) vec.emplace_back(num);
}

int helper(int a, int b) {
	auto zz = sqrtf64(a * a - 4 * b);

	int rl = ceil((a - zz) / 2);
	if (rl * (a - rl) == b) rl += 1;

	int rr = floor((a + zz) / 2);
	if (rr * (a - rr) == b) rr -= 1;

	return rr - rl + 1;
}

// our solver function
void solve() noexcept {
	std::vector<int> times;
	std::vector<int> distances;
	read_line(times);
	read_line(distances);
	long long res{1LL};
	while (!times.empty()) {
		int a = times.back();
		int b = distances.back();
		res *= helper(a, b);
		times.pop_back();
		distances.pop_back();
	}
	std::cout << res << "\n";
}
