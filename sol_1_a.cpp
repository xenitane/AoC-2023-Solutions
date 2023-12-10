/**
 * @file sol_1_a.cpp
 * @author Xenitane
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 * @brief so the basic idea is that you read line by line and find the first and last occouring digits in the line and boom you have the solution from there
 */
void solve() noexcept {
	using namespace std::string_literals;
	std::vector<std::string> nums{"0"s, "1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s};

	long long res{};
	for (std::string str; getline(std::cin, str);) {
		size_t minInd = std::numeric_limits<size_t>::max();
		int	   a{};
		size_t pos{};
		for (int i = 0; const std::string &nn : nums) {
			pos = str.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		res += a * 10;
		std::reverse(str.begin(), str.end());
		minInd = std::numeric_limits<size_t>::max();
		for (int i = 0; const std::string &nn : nums) {
			pos = str.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		res += a;
	}
	std::cout << res;
}