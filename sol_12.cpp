#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int num{}, k{};                                                                                                                                                                                                                                                                                                            \
	while (p + k < n && isdigit(str[p + k])) [[likely]] num = num * 10 + str[p + k++] - 48;                                                                                                                                                                                                                                    \
	p += k - 1

size_t X{}, Y{}, Z{};

template <typename T> using _1dv = std::vector<T>;
template <typename T> using _2dv = _1dv<_1dv<T>>;
template <typename T> using _3dv = _1dv<_2dv<T>>;
template <typename T> using _4dv = _1dv<_3dv<T>>;

enum symbols : char { dot, hash, ques };

long long make_dp(size_t p, size_t np, size_t q, int currnet, _4dv<long long> &dp, const std::string &str, const std::vector<size_t> &nums) noexcept {
	if (p <= X && np <= Y && q <= X) [[unlikely]] {
		if (dp[p][np][q][currnet] == -1) [[likely]] {
			if (p == X) [[unlikely]] {
				dp[p][np][q][currnet] = (np == Y) && !q;
			} else if (np == Y) [[unlikely]] {
				dp[p][np][q][currnet] = (str[p] == hash) ? 0 : make_dp(p + 1, np, 0, 0, dp, str, nums);
			} else {
				switch (str[p]) {
				case dot: dp[p][np][q][currnet] = currnet ? 0 : (make_dp(p + 1, np, 0, 0, dp, str, nums) + make_dp(p + 1, np, 1, 1, dp, str, nums)); break;
				case hash: dp[p][np][q][currnet] = currnet ? ((q == nums[np]) ? make_dp(p + 1, np + 1, 0, 0, dp, str, nums) : make_dp(p + 1, np, q + 1, 1, dp, str, nums)) : 0; break;
				case ques: dp[p][np][q][currnet] = currnet ? ((q == nums[np]) ? make_dp(p + 1, np + 1, 0, 0, dp, str, nums) : make_dp(p + 1, np, q + 1, 1, dp, str, nums)) : (make_dp(p + 1, np, 0, 0, dp, str, nums) + make_dp(p + 1, np, 1, 1, dp, str, nums)); break;
				}
			}
		}
		return dp[p][np][q][currnet];
	} else return 0;
}

long long solve(std::string &str, const std::vector<size_t> nums) noexcept {
	size_t s_len{str.size()}, n_len{nums.size()};
	X = s_len;
	Y = n_len;
	Z = s_len;

	_4dv<long long> dp(s_len + 1, _3dv<long long>(n_len + 1, _2dv<long long>(s_len + 1, _1dv<long long>(2, -1))));

	return make_dp(0, 0, 0, 0, dp, str, nums) + make_dp(0, 0, 1, 1, dp, str, nums);
}
template <typename T> std::vector<T> repeat_vector(const std::vector<T> &vec, size_t p) noexcept {
	std::vector<T> res(0);
	while (p--)
		for (const T &v : vec) res.push_back(v);
	return res;
}

std::string repeat_string(const std::string &str, size_t p) noexcept {
	std::string res;
	while (p--) res.append(str);
	return res;
}

void main_solver() noexcept {
	long long res1{}, res2{};
	for (std::string line; getline(std::cin, line);) {
		std::string data{line.substr(0, line.find(' '))};
		std::transform(data.begin(), data.end(), data.begin(), [](char c) noexcept -> char { return (c == '.' ? 0 : (c == '#' ? 1 : 2)); });
		line = line.substr(line.find(' '));
		size_t				p{}, n{line.size()};
		std::vector<size_t> lens(0);
		while (p < n) {
			if (isdigit(line[p])) [[unlikely]] {
				extract_num(line, num, p, k, n);
				lens.push_back(num);
			}
			p++;
		}

		res1 += solve(data, lens);
		data.push_back(ques);
		data = repeat_string(data, 5);
		lens = repeat_vector(lens, 5);
		data.pop_back();
		res2 += solve(data, lens);
	}

	std::cout << res1 << '\n' << res2 << "\n";
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input12.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}
