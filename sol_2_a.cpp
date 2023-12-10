namespace std {
	vector<string> split(const string &str, char d = ' ') {
		vector<string> res(0);
		size_t		   p = 0, n = str.size();
		string		   temp = ""s;
		while (p < n) {
			if (str[p] == d) [[unlikely]] {
				res.push_back(temp);
				temp = ""s;
			} else [[likely]]
				temp.push_back(str[p]);
			p++;
		}
		res.push_back(temp);
		return res;
	}
} // namespace std

void solve() noexcept {
	int res{};
	for (std::string str; getline(std::cin, str);) {
		str.replace(0, 5, "");
		int game_id					  = std::stoi(str.substr(0, str.find(":")));
		str							  = str.substr(str.find(":") + 1);
		std::vector<std::string> pool = std::split(str, ';');
		bool					 f	  = false;
		while (!pool.empty()) {
			std::vector<std::string> sub_pool = std::split(pool.back(), ',');
			while (!sub_pool.empty()) {
				std::istringstream ss(sub_pool.back());
				int				   c;
				ss >> c;
				ss >> sub_pool.back();
				if (sub_pool.back() == "red" && c > 12) { f = true; }
				if (sub_pool.back() == "green" && c > 13) { f = true; }
				if (sub_pool.back() == "blue" && c > 14) { f = true; }
				sub_pool.pop_back();
			}
			pool.pop_back();
			if (f) break;
		}
		res += f ? 0 : game_id;
	}
	std::cout << res;
}
