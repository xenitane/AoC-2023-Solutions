/**
 * @file sol_4_a.cpp
 * @author Xenitane
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 * @brief read every card, remove card id, then make a set of numbers you have in that card, check how many winning number you have among them and finally add floor of 2 raised to power (count-1).
 */
void solve(int t) noexcept {
	using namespace std::string_literals;
	long long res{};
	for (std::string line; getline(std::cin, line);) {
		int k = 0;
		line.replace(0, line.find(":") + 1, ""s);
		std::istringstream		ss_have(line.substr(0, line.find("|"s)));
		std::istringstream		ss_won(line.substr(line.find("|"s) + 1));
		std::unordered_set<int> have_nums;
		int						i;
		while (ss_have >> i) have_nums.insert(i);
		while (ss_won >> i) k += have_nums.contains(i);
		res += (1 << k) / 2;
	}
	std::cout << res;
}
