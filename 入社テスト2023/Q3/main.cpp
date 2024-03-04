#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

struct Point {
	int x, y;
};

struct Range {
	int i, size;

	public:
		bool operator==(const Range &rh) {
			return i == rh.i && size == rh.size;
		}
};

struct Input {
	int N;
	int penalty;
	std::vector<Point> coords;
};


Input get_input() {
	Input input { 0, 0 };
	std::cin >> input.N >> input.penalty;

	input.coords.resize(input.N);
	for (int i = 0; i < input.N; ++i) {
		std::cin >> input.coords[i].x >> input.coords[i].y;
	}

	return input;
}

Input get_input_from_file(const char *file_path) {
	std::ifstream fs(file_path);
	
	if (fs.is_open()) {
		std::cin.rdbuf(fs.rdbuf());
		return get_input();
	}
	return Input { 0, 0 };
}

double get_squared_error(Input input, Range range) {
	int sum_x = 0;
	int sum_y = 0;
	int sum_x2 = 0;
	int sum_xy = 0;

	for (Point p : input.coords) {
		sum_x += p.x;
		sum_y += p.y;
		sum_x2 += p.x * p.x;
		sum_xy += p.x * p.y;
	}

	double A = 1.0 * (input.N * sum_xy - sum_x * sum_y) / (input.N * sum_x2 - (sum_x * sum_x));
	double B = 1.0 * (sum_y - A * sum_x) / input.N;

	double sum = 0;
	for (Point p : input.coords) {
		double a = p.y - (A * p.x + B);
		sum += a * a;
	}

	return sum;
}

std::unordered_map<Range, double> cache;

double get_least(Input input, std::vector<Range> splits) {
	return 0;
}

int main() {
	//Input input = get_input();
	Input input = get_input_from_file("tc.txt");

	std::cout << get_least(input, { Range { 0, input.N } }) << std::endl;
}