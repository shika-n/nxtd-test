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

class Job {
	private:
		int hours_spent;
		int current_speed;
		int lines_to_write_left;

	public:
		Job(int hours_spent, int current_speed, int lines_to_write_left) : 
			hours_spent(hours_spent),
			current_speed(current_speed),
			lines_to_write_left(lines_to_write_left)
		{}

		void develop(const Rule &rule) {
			lines_to_write_left -= current_speed;
			current_speed = std::max(0, current_speed - rule.reduce_after_dev);
			hours_spent += 1;
		}

		void sleep(const Rule &rule) {
			hours_spent += 3;
			current_speed = std::min(current_speed + rule.gain_after_sleep, rule.max_speed);
		}
		
		static std::pair<int, int> get_potential_and_hours(const Rule &rule, int speed) {
			int pot = 0;
			int hours_taken = 0;

			while (speed > 0) {
				pot += speed;
				speed -= rule.reduce_after_dev;
				hours_taken += 1;
			}

			return std::pair(pot, hours_taken);
		}

		int get_hours_spent() {
			return hours_spent;
		}

		int get_current_speed() {
			return current_speed;
		}

		int get_lines_to_write_left() {
			return lines_to_write_left;
		}
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

int main() {
	Rule rule = get_input();
	// Rule rule =	get_input_from_file("tc.txt");
	Job job(0, rule.max_speed, rule.target);

	while (job.get_lines_to_write_left() > 0) {
		// std::cout << "BEF, Time: " << hours_spent << ", Left: " << lines_to_write_left << "/" << rule.target << ", Current speed: " << current_speed << std::endl;
		if (job.get_current_speed() <= 0) { // speedが0になると寝るしかない
			job.sleep(rule);
		}

		std::pair<int, int> current_potential_hours = Job::get_potential_and_hours(rule, job.get_current_speed());
		int current_potential = current_potential_hours.first;
		float current_efficiency = 1.0f * current_potential / current_potential_hours.second;

		std::pair<int, int> sleep_potential_hours = Job::get_potential_and_hours(rule, std::min(job.get_current_speed() + rule.gain_after_sleep, rule.max_speed));
		int potential_after_sleep = sleep_potential_hours.first;
		float sleep_efficiency = 1.0f * potential_after_sleep / (sleep_potential_hours.second + 3);

		// std::cout << "EFF: " << current_efficiency << " vs " << sleep_efficiency << std::endl;

		// 寝るか開発かどっちが有利
		if (current_potential < job.get_lines_to_write_left() && sleep_efficiency >= current_efficiency) {
			// 寝る
			job.sleep(rule);
		} else {
			// 開発
			job.develop(rule);
			// std::cout << "DEV" << std::endl;
		}

		// std::cout << "AFT, Time: " << hours_spent << ", Left: " << lines_to_write_left << "/" << rule.target << ", Current speed: " << current_speed << std::endl;
		// std::cout << "--\n";
	}

	std::cout << job.get_hours_spent() << std::endl;
}