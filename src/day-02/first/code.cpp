#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

vector<int> get_line_numbers() {
	string number;
	char current;
	vector<int> numbers;

	while ((cin.get(current), current != '\n')) {
		bool reading_has_failed =
			(cin.rdstate() & std::ifstream::failbit) != 0;

		if (current == ' ' && number.empty()) continue;

		if (current == ' ') {
			numbers.push_back(stoi(number));
			number.clear();
			continue;
		}

		if (reading_has_failed) break;

		number += current;
	}

	if (!number.empty()) {
		numbers.push_back(stoi(number));
		number.clear();
	}

	return numbers;
}

bool is_increasing_safe (vector<int> arr) {
	if (arr.size() == 0) return false;

	int greater = arr[0], size = arr.size(), diff;

	for (int i = 1; i < size; i ++) {
		diff = abs(arr[i] - greater);

		if (arr[i] < greater || diff < 1 || diff > 3) return false;

		greater = arr[i];
	}

	return true;
}

bool is_decreasing_safe (vector<int> arr) {
	if (arr.size() == 0) return false;

	int minor = arr[0], size = arr.size(), diff;

	for (int i = 1; i < size; i ++) {
		diff = abs(arr[i] - minor);

		if (arr[i] > minor || diff < 1 || diff > 3) return false;

		minor = arr[i];
	}

	return true;
}

int main () {
	int total = 0;
	vector<int> numbers;

	numbers.push_back(0);

	while (!numbers.empty()) {
		numbers.clear();
		numbers = get_line_numbers();

		if (is_decreasing_safe(numbers) ||
			is_increasing_safe(numbers)) total++;
	};

	numbers.clear();

	cout << total << endl;

	return 0;
}
