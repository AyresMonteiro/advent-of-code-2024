#include <iostream>
#include <algorithm>
#include <fstream>
#include <utility>
#include <vector>

using namespace std;

string get_line() {
	string line;
	char current;

	while ((cin.get(current), current != '\n')) {
		bool reading_has_failed =
			(cin.rdstate() & std::ifstream::failbit) != 0;

		if (reading_has_failed) break;

		line += current;
	}

	return line;
}

vector<pair<int, int>> get_mul_instructions (string line) {
	vector<pair<int, int>> extracted;

	bool negative = false; 
	int idx = 0, digits = 0, first, second;
	string num;

	string instruction("mul(,)");

	for (char c : line) {
		bool is_number_parsing = (idx == 4 || idx == 5),
				is_reading_number = c >= '0' && c <= '9',
				can_append_number = digits < 3;

		if (is_number_parsing && c == '-' && digits == 0 && !negative) {
			num += c;
			negative = true;
		} else if(is_number_parsing && is_reading_number && can_append_number) {
			num += c;
			digits++;
		} else if (c == instruction[idx]) {
			if (digits > 0) {
				if (idx == 4) first = stoi(num);
				if (idx == 5) second = stoi(num);
				num.clear();
				digits = 0;
				negative = false;
			}

			idx++;
		} else {
			idx = 7;
		}

		if (idx >= instruction.size()) {
			if (idx == 6) {
				extracted.push_back(make_pair(first, second));
			}

			idx = 0;
			num.clear();
			digits = 0;
			negative = false;
		}
	}

	return extracted;
}

void print_arr(vector<pair<int, int>> pairs) {
	for(pair<int, int> v : pairs) {
		cout << "(" << v.first << "," << v.second << ") ";
	}

	cout << endl;
}

int main () {
	int total = 0;
	string line;

	while ((line = get_line(), !line.empty())) {
		vector<pair<int, int>> extracted = get_mul_instructions(line);

		for (pair<int, int> v : extracted) {
			total += v.first * v.second;
		}
	}

	cout << total << endl;

	return 0;
}
