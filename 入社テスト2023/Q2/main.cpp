#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


struct Rule {
	int target; // N - Target
	int max_speed; // X - Coding speed
	int reduce_after_dev; // F - Reduce speed by F after writing code
	int gain_after_sleep; // S - Gain speed by S after sleep for 3 hours
};

Rule get_input() {
	Rule rule { 0, 0, 0, 0 };
	std::cin >> rule.target >> rule.max_speed >> rule.reduce_after_dev >> rule.gain_after_sleep;
	return rule;
}

Rule get_input_from_file(const char *file_path) {
	std::ifstream fs(file_path);
	
	if (fs.is_open()) {
		char ch[10];
		std::cin.rdbuf(fs.rdbuf());
		return get_input();
	}
	return Rule { 0, 0, 0, 0 };
}

// speedが0まで、どれくらい行数がかける。そのかかった時間もどのくらいかかる。
int get_potential(Rule rule, int speed, int *hours_taken_ptr = nullptr) {
	int pot = 0;
	int hours_taken = 0;

	while (speed > 0) {
		pot += speed;
		speed -= rule.reduce_after_dev;
		hours_taken += 1;
	}

	if (hours_taken_ptr) {
		*hours_taken_ptr = hours_taken;
	}

	return pot;
}

void sleep(Rule rule, int *hours_spent, int *current_speed) {
	*hours_spent += 3;
	*current_speed = std::min(*current_speed + rule.gain_after_sleep, rule.max_speed);
	// std::cout << "SLEEP" << std::endl;
	// std::cout << "SLP, Time: " << hours_spent << ", Written: " << lines_of_codes_written << "/" << rule.target << ", Current speed: " << current_speed << std::endl;
}

int main() {
	Rule rule = get_input();
	// Rule rule =	get_input_from_file("tc.txt");
	int hours_spent = 0;
	int current_speed = rule.max_speed;
	int lines_to_write_left = rule.target;

	while (lines_to_write_left > 0) {
		// std::cout << "BEF, Time: " << hours_spent << ", Left: " << lines_to_write_left << "/" << rule.target << ", Current speed: " << current_speed << std::endl;
		if (current_speed <= 0) { // speedが0になると寝るしかない
			sleep(rule, &hours_spent, &current_speed);
		}

		int hours_taken = 0;
		int current_potential = get_potential(rule, current_speed, &hours_taken);
		float current_efficiency = 1.0f * current_potential / hours_taken;

		int potential_after_sleep = get_potential(rule, std::min(current_speed + rule.gain_after_sleep, rule.max_speed), &hours_taken);
		float sleep_efficiency = 1.0f * potential_after_sleep / (hours_taken + 3);

		// std::cout << "EFF: " << current_efficiency << " vs " << sleep_efficiency << std::endl;

		// 寝るか開発かどっちが有利
		if (current_potential < lines_to_write_left && sleep_efficiency >= current_efficiency) {
			// 寝る
			sleep(rule, &hours_spent, &current_speed);
		} else {
			// 開発
			lines_to_write_left -= current_speed;
			current_speed = std::max(0, current_speed - rule.reduce_after_dev);
			hours_spent += 1;
			// std::cout << "DEV" << std::endl;
		}

		// std::cout << "AFT, Time: " << hours_spent << ", Left: " << lines_to_write_left << "/" << rule.target << ", Current speed: " << current_speed << std::endl;
		// std::cout << "--\n";
	}

	std::cout << hours_spent << std::endl;
}