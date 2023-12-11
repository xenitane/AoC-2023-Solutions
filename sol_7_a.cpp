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
std::pair<int, int> parse_card(std::string card) {
	std::vector<int> frq(13, 0);
	int				 crd_num{};
	for (char c : card) frq[(crd_num = (crd_num << 4) card_vals(c)) & 14]++;
	std::sort(fbe(frq));
	int priority = (frq[12] == 5) ? 6 : ((frq[12] == 4) ? 5 : ((frq[12] == 3) ? (frq[11] == 2 ? 4 : 3) : ((frq[12] == 2) ? (frq[11] == 2 ? 2 : 1) : 0)));
	return {priority, crd_num};
}

void solve() noexcept {
	long long							   res{};
	std::vector<std::tuple<int, int, int>> cards{};
	for (std::string str; getline(std::cin, str);) {
		std::istringstream iss(str);
		int				   bet;
		iss >> str >> bet;
		auto [pr, val] = parse_card(str);
		cards.emplace_back(pr, val, bet);
	}
	std::sort(fbe(cards));

	for (int i = 1; auto [a, b, c] : cards) res += c * i++;

	std::cout << res << "\n";
}
