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

enum class State {
	kRoot,
	kSleep,
	kDevelop
};

Rule get_input() {
	Rule rule { 0, 0, 0, 0 };
	std::cin >> rule.target >> rule.max_speed >> rule.reduce_after_dev >> rule.gain_after_sleep;
	return rule;
}

Rule get_input_from_file(const char *file_path) {
	std::ifstream fs(file_path);
	
	if (fs.is_open()) {
		std::cin.rdbuf(fs.rdbuf());
		return get_input();
	}
	return Rule { 0, 0, 0, 0 };
}

int get_hours(const Rule &rule, int hours_spent, int current_speed, int lines_left_to_write, State state) {
	if (current_speed <= 0) { // Force Sleep
		hours_spent += 3;
		current_speed = rule.gain_after_sleep;
	} else if (current_speed >= rule.max_speed) { // Force Develop
		hours_spent += 1;
		lines_left_to_write -= current_speed;
		current_speed = std::max(current_speed - rule.reduce_after_dev, 0);
	} else if (state == State::kSleep) { // Sleep
		hours_spent += 3;
		current_speed = std::min(current_speed + rule.gain_after_sleep, rule.max_speed);
	}else if (state == State::kDevelop) { // Develop
		hours_spent += 1;
		lines_left_to_write -= current_speed;
		current_speed = std::max(current_speed - rule.reduce_after_dev, 0);
	}

	if (lines_left_to_write <= 0) {
		return hours_spent;
	}

	return std::min(
		get_hours(rule, hours_spent, current_speed, lines_left_to_write, State::kSleep),
		get_hours(rule, hours_spent, current_speed, lines_left_to_write, State::kDevelop)
	);
}

int main() {
	Rule rule = get_input();
	// Rule rule =	get_input_from_file("tc.txt");

	std::cout << get_hours(rule, 0, rule.max_speed, rule.target, State::kRoot) << std::endl;
}