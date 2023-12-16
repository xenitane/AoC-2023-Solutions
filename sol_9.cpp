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
		std::vector<std::vector<long long>> stck;
		stck.emplace_back(0);
		size_t p{}, n{line.size()};
		int	   num{};
		bool   sign{};
		while (p < n) {
			if (line[p] == '-') [[unlikely]]
				sign = true;
			else if (isdigit(line[p])) {
				extract_num(line, num, p, k, n);
			} else {
				stck.back().push_back(num * (sign ? -1 : 1));
				num	 = 0;
				sign = false;
			}
			p++;
		}
		p = 0;
		while (any_non_zero(stck.back())) {
			n = stck.back().size();
			stck.emplace_back(0);
			for (size_t i{1}; i < n; i++) stck.back().push_back(stck[p][i] - stck[p][i - 1]);
			p++;
		}
		long long tl{}, tr{};
		bool	  f{};
		while (!stck.empty()) {
			tr = stck.back().back() + tr;
			tl = stck.back()[0] - tl;
			f  = !f;
			stck.back().clear();
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