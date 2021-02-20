/* 
Author: William Ko
N15031967
wk700
Program of Conway's Game of Life
*/



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdexcept>
using namespace std;

vector<vector<char>> get_initial_state(string filename) {
	ifstream initial_state("life.txt");
	if (!initial_state) { cerr << "Could not open the file.\n"; }
	else {
		string line;
		vector<vector<char>> rows;
		vector<char> boundary;
		for (int i = 0; i < 22; i++) {
			boundary.push_back(' ');
		}
		rows.push_back(boundary);
		while (getline(initial_state, line)) {
			vector<char> row;
			row.push_back(' ');
			for (int i = 0; i < 20; i++) {
				if (char(line[i]) == '-') {
					row.push_back(' ');
				}
				else {
					row.push_back(char(line[i]));
				}
			}
			row.push_back(' ');
			rows.push_back(row);
		}
		rows.push_back(boundary);
		return rows;
	}	
}

char check_cell_state(char cell) {
	if (cell == ' ') {
		return 'D';
	}
	else {
		return 'A';
	}
}

int check_cell_neighbors(int i, int j, vector<vector<char>> game_state) {
	vector<char> neighbors;
	neighbors.push_back(game_state[i - 1][j - 1]);
	neighbors.push_back(game_state[i][j - 1]);
	neighbors.push_back(game_state[i + 1][j - 1]);
	neighbors.push_back(game_state[i + 1][j]);
	neighbors.push_back(game_state[i - 1][j]);
	neighbors.push_back(game_state[i - 1][j + 1]);
	neighbors.push_back(game_state[i][j + 1]);
	neighbors.push_back(game_state[i + 1][j + 1]);
	int alive_neighbors = 0;
	for (int i = 0; i < 8; i++) {
		if (neighbors[i] == '*'){
			alive_neighbors += 1;
		}
	}
	return alive_neighbors;
}

vector<vector<char>> make_new_game_state() {
	vector<char> row;
	vector<vector<char>> rows;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 22; j++) {
			row.push_back(' ');
		}
		rows.push_back(row);
	}
	return rows;
}

vector<vector<char>> advance_generation(vector<vector<char>> game_state) {
	vector<vector<char>> new_game_state = make_new_game_state();
	vector<vector<int>> will_kill_cell;
	vector<vector<int>> will_make_cell;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 21; j++) {
			char cell_state = check_cell_state(game_state[i][j]);
			int alive_neighbors= check_cell_neighbors(i, j, game_state);
			if ((alive_neighbors <= 3 && alive_neighbors >= 2) && cell_state == 'A') {
				new_game_state[i][j] = '*';
			}
			if (alive_neighbors == 3 && cell_state == 'D') {
				new_game_state[i][j] = '*';
			}
		}
	}
	return new_game_state;
}

int main() {
	vector<vector<char>> rows = get_initial_state("life.txt");
	for (int i = 0; i < 8; i++) {
		string row = "";
		for (int j = 0; j < 20; j++) {
			row += rows[i][j];
		}
		cout << row << endl;
	}

	vector<vector<char>>game_state = rows;
	for (int i = 0; i < 10; i++){
		game_state = advance_generation(game_state);
		for (int i = 1; i < 9; i++) {
			string row = "";
			for (int j = 1; j < 21; j++) {
				row += game_state[i][j];
			}
			cout << row << endl;
		}
	}
}
