void solve() noexcept {
	long long				 res{};
	std::vector<std::string> matrix(1, "");
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
				for (int k = 0; k < p + 1; k++) {
					if ((!isdigit(matrix[i][j + k]) && matrix[i][j + k] != '.') || (!isdigit(matrix[i + 1][j + k]) && matrix[i + 1][j + k] != '.') || (!isdigit(matrix[i + 2][j + k]) && matrix[i + 2][j + k] != '.')) {
						res += std::stoi(matrix[i + 1].substr(j + 1, p - 1));
						break;
					}
				}
				j += p - 2;
			}
		}
	}
	std::cout << res;
}
