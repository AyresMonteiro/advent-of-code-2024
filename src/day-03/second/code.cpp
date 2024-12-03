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

	bool enabled = true, negative = false; 
	int idx = 0, enabler_idx = 0, disabler_idx = 0, digits = 0, first, second;
	string num;

	string mul_instruction("mul(,)");
	string enabler_instruction("do()");
	string disabler_instruction("don't()");

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
		} else if (c == mul_instruction[idx]) {
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

		if (c == enabler_instruction[enabler_idx]) {
			enabler_idx++;
		} else {
			enabler_idx = 0;
		}

		if (c == disabler_instruction[disabler_idx]) {
			disabler_idx++;
		} else {
			disabler_idx = 0;
		}

		if (idx >= mul_instruction.size()) {
			if (idx == 6 && enabled) {
				extracted.push_back(make_pair(first, second));
			}

			idx = 0;
			num.clear();
			digits = 0;
			negative = false;
		}

		if (enabler_idx == enabler_instruction.size()) {
			enabled = true;
		}

		if(disabler_idx == disabler_instruction.size()) {
			enabled = false;
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
	string text;

	// I could make the "enabled" variable static,
	// persisting through function calls, but because
	// I forgot that feature of C *cough cough*, I mean,
	// but because I wanted to respect the concept of pure
	// functions, I decided to just parse the entire text
	// at once
	while ((line = get_line(), !line.empty())) {
		text += line;
	}

	vector<pair<int, int>> extracted = get_mul_instructions(text);

	for (pair<int, int> v : extracted) {
		total += v.first * v.second;
	}

	cout << total << endl;

	return 0;
}
