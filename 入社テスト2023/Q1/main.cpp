#include <fstream>
#include <iostream>
#include <vector>

struct Rules {
	int x;
	int y;
	int a;
};

int get_input(std::vector<Rules> *rules) {
	int n = 0, m = 0;
	std::cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		Rules in { 0, 0, 0 };
		std::cin >> in.x >> in.y >> in.a;
		--in.x;
		--in.y;
		rules->push_back(in);
	}
	return n;
}

int get_input_from_file(std::vector<Rules> *rules, const char *file_path) {
	std::ifstream fs(file_path);
	
	if (fs.is_open()) {
		char ch[10];
		std::cin.rdbuf(fs.rdbuf());
		return get_input(rules);
	}
	return 0;
}

void print_rules(const std::vector<Rules> &rules) {
	for (auto i : rules) {
		std::cout << i.x << " " << i.y << " " << i.a << std::endl;
	}
}

int main() {
	std::vector<Rules> rules;
	// int n = get_input(rules);
	int n = get_input_from_file(&rules, "tc.txt");

	std::vector<int> ans;
	ans.resize(n, 1);

	std::vector<int> prev;
	
	// Apply base rule, 1st pass
	for (auto r : rules) {
		int diff = ans[r.x] - ans[r.y];
		if (diff < r.a) {
			ans[r.x] += r.a - diff;
		}
	}

	prev = ans;
	bool no_sol = false;
	const int pass_n = 5;
	for (int check_pass = 0; check_pass < pass_n; ++check_pass) {
		for (auto r : rules) { // Apply the rule again, nth pass
			int diff = ans[r.x] - ans[r.y];
			if (diff < r.a) { // If diff doesn't comply with the rule, add the minimum difference
				ans[r.x] += r.a - diff;
			}
		}

		bool change = false;
		for (int j = 0; j < prev.size(); ++j) { // Check if answer changed during nth pass
			if (prev[j] != ans[j]) {
				change = true;
				break;
			}
		}
		if (change) {
			// If there are change, move to the next pass
			// If it's the last pass, then mark as no solution
			if (check_pass == pass_n - 1) {
				no_sol = true;
			}
		} else { // If no change, all good
			break;
		}
	}

	if (no_sol) {
		std::cout << -1 << std::endl;
	} else {
		for (auto a : ans) {
			std::cout << a << std::endl;
		}
	}

}