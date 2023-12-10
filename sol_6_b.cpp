void read_line(std::vector<long long> &vec) {
	std::string str;
	std::cin >> str;
	getline(std::cin, str);
	std::istringstream ss(str);
	std::string		   res = "";
	{
		std::string aa;
		while (ss >> aa) res.append(aa);
	}
	std::cerr << res << "\n";
	vec.push_back(std::stoll(res));
}

long long helper(long long a, long long b) {
	auto zz = sqrtf64(a * a - 4 * b);

	long long rl = ceil((a - zz) / 2);
	if (rl * (a - rl) == b) rl += 1;

	long long rr = floor((a + zz) / 2);
	if (rr * (a - rr) == b) rr -= 1;

	return rr - rl + 1;
}

// our solver function
void solve() noexcept {
	std::vector<long long> times;
	std::vector<long long> distances;
	read_line(times);
	read_line(distances);
	long long res{1LL};
	while (!times.empty()) {
		long long a = times.back();
		long long b = distances.back();
		res *= helper(a, b);
		times.pop_back();
		distances.pop_back();
	}
	std::cout << res << "\n";
}