#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

#define UP_LEFT 0
#define UP 1
#define UP_RIGHT 2

#define LEFT 3
#define CENTER 4
#define RIGHT 5

#define DOWN_LEFT 6
#define DOWN 7
#define DOWN_RIGHT 8

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

void print_direction (int direction) {
	switch (direction) {
		case UP_LEFT: cout << "UP_LEFT" << endl; break;
		case UP: cout << "UP" << endl; break;
		case UP_RIGHT: cout << "UP_RIGHT" << endl; break;
		case LEFT: cout << "LEFT" << endl; break;
		case CENTER: cout << "CENTER" << endl; break;
		case RIGHT: cout << "RIGHT" << endl; break;
		case DOWN_LEFT: cout << "DOWN_LEFT" << endl; break;
		case DOWN: cout << "DOWN" << endl; break;
		case DOWN_RIGHT: cout << "DOWN_RIGHT" << endl; break;
		default: cout << "UNKNOWN DIRECTION: " << direction << endl; break;
	}
}

bool search_word (string& word, vector<string>& map, int x, int y, int direction) {
	for (int idx = 0; idx < word.size(); idx++) {
		if (map[y][x] != word[idx])
			return false;

		if (idx == word.size() - 1) break;

		if (direction == UP_LEFT) {
			if (x - 1 < 0 || y - 1 < 0)
				return false;

			x--;	y--;
		} else if (direction == UP) {
			if (y - 1 < 0)
				return false;

			y--;
		} else if (direction == UP_RIGHT) {
			if (x + 1 >= map[y].size() || y - 1 < 0)
				return false;

			x++;	y--;
		} else if (direction == LEFT) {
			if (x - 1 < 0)
				return false;

			x--;
		} else if (direction == RIGHT) {
			if (x + 1 >= map[y].size())
				return false;

			x++;
		} else if (direction == DOWN_LEFT) {
			if (x - 1 < 0 || y + 1 >= map.size())
				return false;

			x--;	y++;
		} else if (direction == DOWN) {
			if (y + 1 >= map.size())
				return false;

			y++;
		} else if (direction == DOWN_RIGHT) {
			if (x + 1 >= map[y].size() || y + 1 >= map.size())
				return false;

			x++;	y++;
		}
	}

	return true;
}

int search_all_xmas_around (vector<string>& map) {
	int total = 0;
	string word("MAS");

	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] != 'A') continue;

			vector<pair<pair<int, int>, int>> instructions;

			if (x - 1 >= 0 && y - 1 >= 0 && map[y - 1][x - 1] == 'M')
				instructions.push_back(make_pair(
					make_pair(x - 1, y - 1),
					DOWN_RIGHT
				));

			if (x + 1 < map[y].size() && y - 1 >= 0 && map[y - 1][x + 1] == 'M')
				instructions.push_back(make_pair(
					make_pair(x + 1, y - 1),
					DOWN_LEFT
				));

			if (x - 1 >= 0 && y + 1 < map.size() && map[y + 1][x - 1] == 'M')
				instructions.push_back(make_pair(
					make_pair(x - 1, y + 1),
					UP_RIGHT
				));

			if (x + 1 < map[y].size() && y + 1 < map.size() && map[y + 1][x + 1] == 'M')
				instructions.push_back(make_pair(
					make_pair(x + 1, y + 1),
					UP_LEFT
				));

			if (instructions.size() != 2) continue;

			bool found_first = search_word(
				word,
				map,
				instructions[0].first.first,
				instructions[0].first.second,
				instructions[0].second
			);

			bool found_second = search_word(
				word,
				map,
				instructions[1].first.first,
				instructions[1].first.second,
				instructions[1].second
			);

			if(!found_first || !found_second) continue;

			total++;
		}
	}

	return total;
}

int main () {
	string current;
	vector<string> map;

	while ((current = get_line(), !current.empty())) {
		map.push_back(current);
	}

	cout << search_all_xmas_around(map) << endl;

	return 0;
}
