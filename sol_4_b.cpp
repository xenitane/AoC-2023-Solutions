/**
 * @file sol_4_b.cpp
 * @author Xenitane
 * @date 2023-12-10
 *
 * @copyright Copyright (c) 2023
 *
 * @brief read every card, remove card id, then make a set of numbers you have in that card, check how many winning number you have among them and add the count of the current card to the next cards you'll win.
 */

void solve(int t) noexcept {
	while (t--) {
		// todo: write code here to solve the problem at hand
		using namespace std::string_literals;
		long long		 res{};
		int				 c{};
		std::vector<int> data{0};
		for (std::string line; getline(std::cin, line);) {
			if (c + 1 > (int)data.size()) data.resize(c + 1, 0);
			data[c]++;
			int k = 0;
			line.replace(0, line.find(":") + 1, ""s);
			std::istringstream		ss_have(line.substr(0, line.find("|"s)));
			std::istringstream		ss_won(line.substr(line.find("|"s) + 1));
			std::unordered_set<int> have_nums;
			int						i;
			while (ss_have >> i) have_nums.insert(i);
			while (ss_won >> i) k += have_nums.contains(i);
			if (c + k + 1 > (int)data.size()) data.resize(c + k + 1, 0);
			for (int j = 1; j <= k; j++) data[c + j] += data[c];
			res += data[c];
			c++;
		}
		std::cout << res;
	}
}