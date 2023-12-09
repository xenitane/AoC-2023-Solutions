/**
 * @file sol_1_b.cpp
 * @author Xenitane
 * @date 2023-12-09
 *
 * @copyright Copyright (c) 2023
 *
 * @brief so the basic idea is that you read line by line and find the first and last occouring digits and the english representation of it in the line and boom you have the solution from there
 */

void solve() noexcept {
	std::vector<std::string> nums{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	std::vector<std::string> nums_names{"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	std::vector<std::string> nums_names_rev{"orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};

	long long res{0LL};
	for (std::string str; getline(std::cin, str);) {
		size_t minInd = std::numeric_limits<size_t>::max();
		int	   a	  = 0;
		for (int i = 0; i < 10; i++) {
			size_t zz;
			zz = str.find(nums[i]);
			if (zz < minInd) minInd = zz, a = i;
			zz = str.find(nums_names[i]);
			if (zz < minInd) minInd = zz, a = i;
		}
		res += a * 10;
		std::reverse(str.begin(), str.end());
		minInd = std::numeric_limits<size_t>::max();
		for (int i = 0; i < 10; i++) {
			size_t zz;
			zz = str.find(nums[i]);
			if (zz < minInd) minInd = zz, a = i;
			zz = str.find(nums_names_rev[i]);
			if (zz < minInd) minInd = zz, a = i;
		}
		res += a;
	}
	std::cout << res;
}