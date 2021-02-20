/*

William Ko N15031967
Recitation #03
Professor Sterling
This program includes a minesweeper class and a Tile struct

*/



#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include<stdio.h>
using namespace std;


struct Tile{
public:
	string value;
	bool is_visible;
	bool is_bomb;
	Tile(bool is_bomb, bool is_visible): is_bomb(is_bomb), is_visible(is_visible){
		if(is_bomb){
			value = "*";
		}
		else{
			value = "1";
		}
	}
	void display(){
		if(is_visible){
			cout << value;
		}
		else{
			cout << "0";
		}
	}
private:

};

class Minesweeper{
public:
	int rows;
	int cols;
	vector<vector<Tile>> board;
	Minesweeper(){
	 	rows = 10;
		cols = 10;
		vector<Tile> first_row;
		vector<Tile> last_row;
		for(int i = 0; i < cols+2; i++){
			first_row.push_back(Tile(false,true));
		}
		board.push_back(first_row);
		for(int i = 0; i < rows; i++){
			vector<Tile> tile_row;
			for(int j = 0; j < cols+2; j++){
				if(j == 0){
					tile_row.push_back(Tile(false,true));
					continue;
				}
				if(j == cols+1){
					tile_row.push_back(Tile(false,true));
					continue;
				}
				else{
					int r_num = rand() % 10;
					if(r_num == 5 || r_num == 7){
						tile_row.push_back(Tile(true, false));
					}
					else{
						tile_row.push_back(Tile(false,false));
					}
				}
			}
			board.push_back(tile_row);
		}
		for(int i = 0; i < cols+2; i++){
			last_row.push_back(Tile(false,true));
		}
		board.push_back(last_row);
		for(int i = 1; i < rows+1; i++){
			for(int j = 1; j < cols+1; j++){
				if(!board[i][j].is_bomb){
					board[i][j].value = to_string(surrounding_bombs(i,j));
				}
			}
		}
	}
	void display(bool display_bombs){
		if(display_bombs){
			for(int i = 1; i < rows+1; i++){
				for(int j = 1; j < cols+1; j++){
					board[i][j].is_visible = true;
					board[i][j].display();
				}
				cout << endl;
			}
		}
		else{
			for(int i = 1; i < rows+1; i++){
				for(int j = 1; j < cols+1; j++){
					board[i][j].display();
				}
				cout << endl;
			}
		}
	}
	bool validRow(int r){
		if(r < rows && r >= 1){
			return true;
		}
		else{
			return false;
		}
	}
	bool validCol(int c){
		if(c < cols && c >= 1){
			return true;
		}
		else{
			return false;
		}
	}
	bool isVisible(int r, int c){
		return board[r][c].is_visible;
	}
	bool done(){
		for(int r = 0; r < rows; r++){
			for(int c = 0; c < cols; c++){
				if(!board[r][c].is_visible && !board[r][c].is_bomb){
					return false;
				}
			}
		}
		return true;
	}
	bool play(int r, int c){
		if(board[r][c].is_bomb){
			return false;
		}
		else{
			int bombs = surrounding_bombs(r,c);
			if(bombs != 0){
				board[r][c].is_visible = true;
				return true;
			}
			if(bombs == 0){
				board[r][c].is_visible = true;
				if(!board[r][c+1].is_visible){
					board[r][c+1].is_visible = true;
					if(surrounding_bombs(r,c+1) == 0){
						play(r, c+1);
					}
				}
				if(!board[r+1][c+1].is_visible){
					board[r+1][c+1].is_visible = true;
					if(surrounding_bombs(r+1,c+1) == 0){
						play(r+1, c+1);
					}
				}
				if(!board[r+1][c].is_visible){
					board[r+1][c].is_visible = true;
					if(surrounding_bombs(r+1,c) == 0){
						play(r+1, c);
					}
				}
				if(!board[r+1][c-1].is_visible){
					board[r+1][c-1].is_visible = true;
					if(surrounding_bombs(r+1,c-1) == 0){
						play(r+1, c-1);
					}
				}
				if(!board[r][c-1].is_visible){
					board[r][c-1].is_visible = true;
					if(surrounding_bombs(r,c-1) == 0){
						play(r, c-1);
					}
				}
				if(!board[r-1][c-1].is_visible){
					board[r-1][c-1].is_visible = true;
					if(surrounding_bombs(r-1,c-1) == 0){
						play(r-1, c-1);
					}
				}
				if(!board[r-1][c].is_visible){
					board[r-1][c].is_visible = true;
					if(surrounding_bombs(r-1,c) == 0){
						play(r-1, c);
					}
				}
				if(!board[r-1][c+1].is_visible){
					board[r-1][c+1].is_visible = true;
					if(surrounding_bombs(r-1,c+1) == 0){
						play(r-1, c+1);
					}
				}
				return true;
			}
		}
	}
	int surrounding_bombs(int r, int c){
		int bombs = 0;
		if(board[r+1][c].is_bomb){
			bombs += 1;
		}
		if(board[r-1][c].is_bomb){
			bombs += 1;
		}
		if(board[r+1][c+1].is_bomb){
			bombs += 1;
		}
		if(board[r+1][c-1].is_bomb){
			bombs += 1;
		}
		if(board[r-1][c+1].is_bomb){
			bombs += 1;
		}
		if(board[r-1][c-1].is_bomb){
			bombs += 1;
		}
		if(board[r][c+1].is_bomb){
			bombs += 1;
		}
		if(board[r][c-1].is_bomb){
			bombs += 1;
		}
		return bombs;
	}
private:
};


int main(){
    Minesweeper sweeper;
    // Continue until only invisible cells are bombs
    while (!sweeper.done()) {
        sweeper.display(false); // display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            cout << "row? ";
            cin >> r;
            if (!sweeper.validRow(r)) {
                cout << "Row out of bounds\n";
                continue;
            }
            cout << "col? ";
            cin >> c;
            if (!sweeper.validCol(c)) {
                cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown

}
