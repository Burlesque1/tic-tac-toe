#include "player.h"

player::player(){
	
	state = {{X, X, X, O}, {O, X, X, X}, {O, O, E, E}, {O, E, E, E}};
	
	next_move.first = -1;
	
	next_move.second = -1;
}

long long player::show_recurr(){
	
	return recurr_count;
	
}

void player::get_board(vector<vector<entry>> board, int step){
		
		curr_step = step;
		
		state = board;	// can be optimized 
}

void player::get_last_move(pair<int, int> last_move, int step){
	
	int row = last_move.first, column = last_move.second;
	
	state[row][column] = O;
	
	curr_step = step;
	
	curr_encode += pow(3, (row * BOARD_COLUMN + column));
}	

pair<int, int> player::return_move(){	
	
	alpha_beta_search();
	
	state[next_move.first][next_move.second] = X;
	
	curr_encode += 2*pow(3, (next_move.first * BOARD_COLUMN + next_move.second));
	
	return next_move;
}


long long player::generate_encode(int row, int column){
	
	return curr_encode + pow(3, (row * BOARD_COLUMN + column));
}


int player::return_utility(vector<vector<entry>> &state){
	int res = 0;
	// chcek rows
	for(int i=0;i<BOARD_ROW;i++){
		auto tmp = state[i][0];
		bool tag = true;
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != tmp){
				tag = false;
				break;
			}
		}
		if(tag)
			res = tmp == X ? 1000 : tmp == E ? 0 : -1000;
		if(res)
			return res;
	}
	
	// check columns
	for(int i=0;i<BOARD_COLUMN;i++){
		auto tmp = state[0][i];
		bool tag = true;
		for(int j=0;j<BOARD_ROW;j++){
			if(state[j][i] != tmp){
				tag = false;
				break;
			}
		}
		if(tag)
			res = tmp == X ? 1000 : tmp == E ? 0 : -1000;
		if(res)
			return res;
	}
	
	// check diagnols
	bool tag = true;
	for(int i=0, j=0;i<BOARD_ROW && j<BOARD_COLUMN;i++, j++){
		if(state[i][j] != state[0][0]){
			tag = false;
			break;
		}
	}
	if(tag)
		res = state[0][0] == X ? 1000 : state[0][0] == E ? 0 : -1000;
	if(res)
		return res;	
	tag = true;	
	for(int i=0, j=0;i<BOARD_ROW && j<BOARD_COLUMN;i++, j++){
		if(state[i][BOARD_COLUMN-1-j] != state[0][BOARD_COLUMN-1]){
			tag = false;
			break;
		}
	}
	if(tag)
		res = state[0][BOARD_COLUMN-1] == X ? 1000 : state[0][BOARD_COLUMN-1] == E ? 0 : -1000;
	if(res)
		return res;
	return res;
}

void player::alpha_beta_search(){
	// if first step set X into middle
	;
	
	cout<<"curr step "<<curr_step<<endl;
	next_move.first = -1;
	next_move.second = -1;
	int value = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){		
			if(state[i][j] != E)				
				continue;
			if(next_move.first == -1){
				next_move.first = i;
				next_move.second = j;
			}
			state[i][j] = X;
			int max_u = 1000, min_u = -1000;	
			time_t start = time(nullptr);
			int v = min_value(min_u, max_u, curr_step+1);
			
			state[i][j] = E;
			cout<<v<<" i = "<<i<<" j = "<<j<<endl;	
			if(v > value){
				value = v;
				next_move.first = i;
				next_move.second = j;
				cout<<"value = "<<value<<" i= "<<i<<" j= "<<j<<endl;			
			}
		}
	}
}

int player::min_value(int &alpha, int &beta, int steps){
	recurr_count++;
	int utility = return_utility(state);
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN)
		return utility;
	
	int v = 1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			state[i][j] = O;
			v = min(v, max_value(alpha, beta, steps+1));
			state[i][j] = E;
			if(v <= alpha){
				return v;
			}
			beta = min(v, beta);
		}		
	}
	return v;
}

int player::max_value(int &alpha, int &beta, int steps){
	recurr_count++;
	int utility = return_utility(state);
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN)
		return utility;
	
	int v = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)	
				continue;
			state[i][j] = X;	
			v = max(v, min_value(alpha, beta, steps+1));
			state[i][j] = E;
			if(v>=beta){
				return v;
			}
			alpha = max(alpha, v);
		}
	}
	return v;
}

