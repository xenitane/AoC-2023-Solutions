#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

#define extract_num(str, num, p, k, n)                                                                                                                                                                                                                                                                                         \
	int k{};                                                                                                                                                                                                                                                                                                                   \
	while (p + k < n && isdigit(str[p + k])) [[likely]] num = num * 10 + str[p + k++] - 48;                                                                                                                                                                                                                                    \
	p += k - 1

bool any_non_zero(const std::vector<long long> &vec) {
	for (const long long &i : vec)
		if (i) [[likely]]
			return true;
	return false;
}

void main_solver() noexcept {
	long long resl{}, resr{};
	for (std::string line; getline(std::cin, line);) {
		std::vector<std::vector<long long>> stck(0);
		stck.emplace_back(1, 0);
		size_t p{}, n{line.size()};
		bool   sign{};
		while (p < n) {
			if (line[p] == '-') [[unlikely]]
				sign = true;
			else if (isdigit(line[p])) [[unlikely]] {
				extract_num(line, stck.back().back(), p, k, n);
				if (sign) stck.back().back() *= -1;
			} else {
				stck.back().push_back(0);
				sign = false;
			}
			p++;
		}
		p = 0;
		n = stck.back().size();
		while (any_non_zero(stck.back())) {
			stck.emplace_back(--n);
			for (size_t i{}; i < n; i++) stck[p + 1][i] = stck[p][i + 1] - stck[p][i];
			p++;
		}
		long long tl{}, tr{};
		while (!stck.empty()) {
			tr = stck.back().back() + tr;
			tl = stck.back()[0] - tl;
			stck.pop_back();
		}
		resr += tr;
		resl += tl;
	}
	std::cout << resr << '\n' << resl << '\n';
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input9.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}