#include "tic_tac_toe.h"

class player{

private:	
	pair<int, int> next_move;	
	
	// board state
	vector<vector<entry>> state;
	
	int ai_level;
	
	bool cutoff;
	 
	int curr_step;
	
	int depth;
	
	int max_prune;
	
	int min_prune;
	
	long long curr_encode;
	
	static long long recurr_count;	
	
	// <encoding, utility>
	unordered_map<long long, int> memo;
	
	long long generate_encode(int row, int column);
	
	int terminal_test(vector<vector<entry>> &state);
	
	void print_state();
	
	// search
	void alpha_beta_search();
	
	int max_value(int row, int column, int alpha, int beta, int steps, int &dep);
	
	int min_value(int row, int column, int alpha, int beta, int steps, int &dep);

public:	
	player(int level);
	
	void print_info();
	
	void get_last_move(pair<int, int> last_move, int step);
	
	// move
	pair<int, int> return_move();
};
