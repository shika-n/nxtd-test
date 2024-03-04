#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include <bitset>

struct Input {
	int N;
	int K;
};


Input get_input() {
	Input input { 0, 0 };
	std::cin >> input.N >> input.K;

	return input;
}

void print_test() {
	const int N = 8;

	std::cout << std::pow(2, N) << std::endl;
	for (int k = 2; k <= N; ++k) {
		int sum = 0;
		std::string needle0 = "";
		std::string needle1 = "";
		for (int j = 0; j < k; ++j) {
			needle0 += "0";
			needle1 += "1";
		}
		for (int i = 0; i < std::pow(2, N); ++i) {
			std::string bin = std::bitset<N>(i).to_string();
			if (bin.find(needle0) != std::string::npos || bin.find(needle1) != std::string::npos) {
				sum += 1;
			}
		}
		std::cout << k << " - " << sum << std::endl;
	}
}

u_int64_t get_occurance(int N, int K, char parent, char now, int depth, int streak) {
	if (parent == now) {
		streak += 1;
	} else {
		streak = 1;
	}

	if (streak >= K) {
		// std::cout << "> " << parent << now << " " << depth << " " << std::pow(2, N - (depth)) << std::endl;
		return std::pow(2, N - (depth));
	}
	
	if (depth >= N) {
		return 0;
	}

	return get_occurance(N, K, now, '0', depth + 1, streak) + 
		get_occurance(N, K, now, '1', depth + 1, streak);
}

int main() {
	// print_test();

	Input input = get_input();

	// int NKdiff = input.N - input.K;
	// u_int64_t variance = std::pow(2, NKdiff);
	// long double half_sum = variance * (1.0 + 0.5 * NKdiff); // 1.0 * variance + 0.5 * variance * NKdiff
	// std::cout << "NKdiff: " << NKdiff << ", varianace: " << variance << std::endl;
	// std::cout << "sizeof(half_sum): " << sizeof(half_sum) << std::endl;
	// std::cout << std::setprecision(9) << 1.0 - (2.0 * half_sum / std::pow(2, input.N)) << std::endl;

	u_int64_t sum = get_occurance(input.N, input.K, ' ', '0', 1, 1) + get_occurance(input.N, input.K, ' ', '1', 1, 1);
	std::cout << std::setprecision(9) << 1.0 - (sum / std::pow(2, input.N)) << std::endl;
}