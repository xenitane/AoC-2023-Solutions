#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

using namespace std::string_literals;

const std::vector<std::string> num_names{"\157\156\145"s, "\164\167\157"s, "\164\150\162\145\145"s, "\146\157\165\162"s, "\146\151\166\145"s, "\163\151\170"s, "\163\145\166\145\156"s, "\145\151\147\150\164"s, "\156\151\156\145"s};
const std::vector<int>		   num_lens{3, 3, 5, 4, 4, 3, 5, 5, 4};

bool sub_str_present_at(const std::string &src, const std::string &sub, const size_t sp) noexcept {
	for (size_t i{}; const char c : sub)
		if (src[sp + (i++)] ^ c) return false;
	return true;
}

void solve(const std::vector<std::string> &lines) noexcept {

	int res1{}, res2{};
	for (const std::string &line : lines) {
		int	   a{}, b{}, c{}, d{};
		size_t len{line.size()};
		for (size_t i{}; i < len; i++) {
			if (isdigit(line[i])) {
				b = line[i] - 48;
				a = a ? a : b;
				d = line[i] - 48;
				c = c ? c : d;
			}
			for (int j{}; const std::string &num_name : num_names)
				if ((i + num_lens[j++] <= len) && sub_str_present_at(line, num_name, i)) {
					d = j;
					c = c ? c : d;
					break;
				}
		}
		res1 += a * 10 + b;
		res2 += c * 10 + d;
	}
	std::cout << res1 << '\12' << res2 << '\12';
}

void main_solver() noexcept {
	std::vector<std::string> lines;
	for (std::string line; getline(std::cin, line);) lines.push_back(line);
	solve(lines);
}

int main() noexcept {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	std::cerr.tie(0);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	freopen("error.txt", "w", stderr);
	main_solver();

	return 0;
}