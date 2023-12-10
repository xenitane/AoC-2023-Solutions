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
	long long res{};
	for (std::string str; getline(std::cin, str);) {
		struct local_data {
			int r, g, b;
			local_data() : r(0), g(0), b(0) {}
			void add(int r, int g, int b) { this->r = std::max(this->r, r), this->g = std::max(this->g, g), this->b = std::max(this->b, b); }
			int	 fin() { return this->r * this->g * this->b; }
		} data;
		str							  = str.substr(str.find(":") + 1);
		std::vector<std::string> pool = std::split(str, ';');
		while (!pool.empty()) {
			std::vector<std::string> sub_pool = std::split(pool.back(), ',');
			int						 r{}, g{}, b{};
			while (!sub_pool.empty()) {
				std::istringstream ss(sub_pool.back());
				int				   c;
				ss >> c;
				ss >> sub_pool.back();
				if (sub_pool.back() == "red") r = c;
				if (sub_pool.back() == "green") g = c;
				if (sub_pool.back() == "blue") b = c;
				data.add(r, g, b);
				sub_pool.pop_back();
			}
			pool.pop_back();
		}
		res += data.fin();
	}
	std::cout << res;
}
