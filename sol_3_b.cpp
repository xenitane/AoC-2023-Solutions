void solve() noexcept {
	long long								  res{};
	std::unordered_map<int, std::vector<int>> data;
	std::vector<std::string>				  matrix(1, "");
	for (std::string str; getline(std::cin, str);) matrix.push_back('.' + str + '.');
	matrix[0].assign(matrix[1].size(), '.');
	matrix.push_back(matrix[0]);
	int n = matrix.size() - 2;
	int m = matrix[1].size() - 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (isdigit(matrix[i + 1][j + 1])) {
				int p = 2;
				while (isdigit(matrix[i + 1][j + p])) p++;
				int num = std::stoi(matrix[i + 1].substr(j + 1, p - 1));
				for (int k = 0; k < 3; k++)
					for (int l = 0; l < p + 1; l++)
						if (matrix[i + k][j + l] == '*') data[((i + k) << 16) + (j + l)].push_back(num);

				j += p - 2;
			}
		}
	}
	matrix.clear();
	for (auto &&[_, dd] : data)
		if (dd.size() == 2) res += dd[0] * dd[1];
	std::cout << res;
}