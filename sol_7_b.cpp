int card_vals(char c) noexcept {
	switch (c) {
	case '2': return 1;
	case '3': return 2;
	case '4': return 3;
	case '5': return 4;
	case '6': return 5;
	case '7': return 6;
	case '8': return 7;
	case '9': return 8;
	case 'T': return 9;
	case 'Q': return 10;
	case 'K': return 11;
	case 'A': return 12;
	case 'J': return 13;
	default: return -1;
	}
}

int handle_js(std::string card) noexcept {
	for (char &c : card) c = 'a' + card_vals(c);
	std::vector<int> frq(13, 0);
	for (char c : card) frq[c - 'b']++;
	std::sort(frq.begin(), frq.begin() + 12);
	frq[11] += frq[12];
	return (frq[11] == 5) ? 6 : ((frq[11] == 4) ? 5 : ((frq[11] == 3) ? (frq[10] == 2 ? 4 : 3) : ((frq[11] == 2) ? (frq[10] == 2 ? 2 : 1) : 0)));
}

// our solver function
void solve() noexcept {
	long long									   res{};
	std::vector<std::tuple<int, std::string, int>> cards{};
	for (std::string str; getline(std::cin, str);) {
		std::istringstream iss(str);
		int				   bet;
		iss >> str >> bet;
		int pr = handle_js(str);
		for (char &c : str)
			if (c == 'J') c = 'a';
			else c = 'a' + card_vals(c);
		cards.emplace_back(pr, str, bet);
	}
	std::sort(cards.begin(), cards.end());
	for (int i = 1; auto [a, b, c] : cards) res += c * i++;

	std::cout << res << "\n";
}
