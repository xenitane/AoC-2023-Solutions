#pragma GCC optimize("O3,Os,unroll-loops")
#pragma GCC target("avx2,sse4.2,popcnt,lzcnt,abm,bmi,bmi2")

#include <bits/stdc++.h>

using namespace std::string_literals;

std::vector<std::string> nums{"0"s, "1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s};
std::vector<std::string> nums_names{"zero"s, "one"s, "two"s, "three"s, "four"s, "five"s, "six"s, "seven"s, "eight"s, "nine"s};
std::vector<std::string> nums_names_rev{"orez"s, "eno"s, "owt"s, "eerht"s, "ruof"s, "evif"s, "xis"s, "neves"s, "thgie"s, "enin"s};

void solve(const std::vector<std::string> &lines, const std::vector<std::vector<std::string> *> &num_data) noexcept {

	long long res{};
	for (std::string line : lines) {
		size_t minInd = std::numeric_limits<size_t>::max();
		int	   a{};
		size_t pos{};
		for (int i = 0; const std::string &nn : *num_data[0]) {
			pos = line.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		for (int i = 0; const std::string &nn : *num_data[1]) {
			pos = line.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		res += a * 10;
		std::reverse(line.begin(), line.end());
		minInd = std::numeric_limits<size_t>::max();
		for (int i = 0; const std::string &nn : *num_data[0]) {
			pos = line.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		for (int i = 0; const std::string &nn : *num_data[2]) {
			pos = line.find(nn);
			if (pos < minInd) minInd = pos, a = i;
			i++;
		}
		res += a;
	}
	std::cout << res << "\n";
}

void solve_part_1(const std::vector<std::string> &lines) noexcept {
	std::unique_ptr<std::vector<std::string>> aa(new std::vector<std::string>(0));
	solve(lines, {&nums, aa.get(), aa.get()});
}
void solve_part_2(const std::vector<std::string> &lines) noexcept { solve(lines, {&nums, &nums_names, &nums_names_rev}); }

void main_solver() noexcept {
	std::vector<std::string> lines;
	for (std::string line; getline(std::cin, line);) lines.push_back(line);
	solve_part_1(lines);
	solve_part_2(lines);
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