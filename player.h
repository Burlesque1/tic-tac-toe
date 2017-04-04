#include "tic_tac_toe.h"

class player{

private:	
	pair<int, int> next_move;	
	
	// board state
	vector<vector<entry>> state;
	
	int curr_step;
	
	static long long recurr_count;	
	
	int return_utility(vector<vector<entry>> &state);
	
	// search
	void alpha_beta_search();
	
	int max_value(int &alpha, int &beta, int steps);
	
	int min_value(int &alpha, int &beta, int steps);

public:	
	player();
	
	void get_board(vector<vector<entry>> board, int step);
	
	long long show_recurr();
	// move
	pair<int, int> return_move();
};
