#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

string get_line_numbers() {
	string line;
	char current;

	while ((cin.get(current), current != '\n')) {
		bool reading_has_failed =
			(cin.rdstate() & std::ifstream::failbit) != 0;

		if (reading_has_failed) break;

		int current_line_size = line.size();

		bool line_is_empty = current_line_size == 0;
		bool previous_is_whitespace =
			!line_is_empty && line[current_line_size - 1] == ' ';

		if (current == ' ' &&
			(line_is_empty || previous_is_whitespace)) continue;

		line += current;
	}

	return line;
}

pair<int, int> get_int_pair_from_line(string line) {
	std::size_t whitespace_idx = line.find(' ');

	string first = line.substr(0, whitespace_idx);
	string second =
		line.substr(whitespace_idx + 1, line.size() - whitespace_idx);

	pair<int, int> result = make_pair(stoi(first), stoi(second));

	return result;
}

int main () {
	vector<vector<int>> data_sets;
	data_sets.reserve(2);
	data_sets.push_back(vector<int>());
	data_sets.push_back(vector<int>());

	string l;
	
	while ((l = get_line_numbers(), !l.empty())) {
		pair<int, int> numbers = get_int_pair_from_line(l);

		data_sets[0].push_back(numbers.first);
		data_sets[1].push_back(numbers.second);
	}

	sort(data_sets[0].begin(), data_sets[0].end());
	sort(data_sets[1].begin(), data_sets[1].end());

	int size = data_sets[0].size();

	int total = 0;

	for (int i = 0; i < size; i++) {
		total += abs(data_sets[0][i] - data_sets[1][i]);
	}

	cout << total << endl;

	return 0;
}
