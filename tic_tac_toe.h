#include <iostream>
#include <vector>
#include <ctime>
#include <unordered_map>
#include <cmath>

#define BOARD_ROW 4
#define BOARD_COLUMN 4
#define TARGET 4
#define DEPTH_LIMIT 8

using namespace std; 

#ifndef _ENTRY_
#define _ENTRY_

enum entry {
		O, X, E
	};

class tic_tac_toe{

private:
	vector<vector<entry>> board;
	
	bool check_winner(int row, int column);
	
	pair<int, int> last_move;
	
	int step_count;
	
	entry curr_player;
	
public:
	
	tic_tac_toe();
	
	bool next(int row, int column, entry en); 
	
	bool check_input(int row, int column);
	
	vector<vector<entry>> return_board();
	
	int return_step();
	
	pair<int, int> return_last_move();
	
	void show_info();
	
	void print_board();
	
};
#endif
