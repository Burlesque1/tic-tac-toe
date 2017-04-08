#include "player.h"

player::player(){
	
//	state = {{X, X, X, O}, {X, X, O, E}, {O, X, E, E}, {O, O, O, E}};
	
	state = vector<vector<entry>>(BOARD_ROW, vector<entry>(BOARD_COLUMN, E));
	
	curr_encode = 0;
	
	next_move.first = -1;
	
	next_move.second = -1;
	
	memo = unordered_map<long long, int>();
}

long long player::show_recurr(){
	
	return recurr_count;
	
}

void player::test(){
//	for(auto m:memo){
//		cout<<m.first<<" "<<m.second<<endl;
//	}
	cout<<memo.size()<<endl;
}

void player::get_last_move(pair<int, int> last_move, int step){
	
	int row = last_move.first, column = last_move.second;
	
	curr_step = step;	
	
	if(row != -1 && column != -1){
		
		state[row][column] = O;
	
		curr_encode += pow(3, (row * BOARD_COLUMN + column));
	}
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

void player::print_state(){
	cout<<"\n\n\n";
	for(auto s:state){
		for(auto ss:s){
			if(ss == E)
				cout<<"- ";
			else
				cout<<ss<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int player::terminal_test(vector<vector<entry>> &state){
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
			
			curr_encode += 2*pow(3, (i * BOARD_COLUMN + j));
			
			int max_u = 1000, min_u = -1000;
			
			time_t start = time(nullptr);
				
			int v = min_value(i, j, min_u, max_u, curr_step+1);
			
			state[i][j] = E;
			curr_encode -= 2*pow(3, (i * BOARD_COLUMN + j));
			cout<<time(nullptr)-start<<"s "<<v<<" i = "<<i<<" j = "<<j<<endl;	
			
			if(v > value){
				value = v;
				next_move.first = i;
				next_move.second = j;
				cout<<"value = "<<value<<" i= "<<i<<" j= "<<j<<endl;			
			}
		}
	}
//	cout<< curr_encode<<"  dfas "<<endl;
}

int player::min_value(int row, int column, int alpha, int beta, int steps){
//	cout<<curr_encode<<" min "<<endl;
	recurr_count++;
	
	if(memo.find(curr_encode) != memo.end())
		return memo[curr_encode];
		
	int utility = terminal_test(state);
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN){
		memo[curr_encode] = utility;	
		return utility;
	}
	
	int v = 1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			
			state[i][j] = O;
			curr_encode += pow(3, (i * BOARD_COLUMN + j));
//			if(row == 1 && column == 3 && steps == 14){
//				cout<<" min --- "<<v<<" i "<<i<<" j "<<j<<" alpha "<<alpha<<endl;
//			}
			v = min(v, max_value(i, j, alpha, beta, steps+1));
			
//			if(row == 1 && column == 3 && steps == 14){
//				cout<<" --- min "<<v<<" i "<<i<<" j "<<j<<" alpha "<<alpha<<endl;
////				print_state();
//			}
			
			state[i][j] = E;
			
			curr_encode -= pow(3, (i * BOARD_COLUMN + j));
			
			if(v <= alpha){
				if(steps >= DEPTH_LIMIT)
					memo[curr_encode] = v;
				return v;
			}
			beta = min(v, beta);
		}		
	}
	if(steps >= DEPTH_LIMIT)
		memo[curr_encode] = v;	
	return v;
}

int player::max_value(int row, int column, int alpha, int beta, int steps){
//	cout<<curr_encode<<" max "<<endl;
	recurr_count++;
	
	if(memo.find(curr_encode) != memo.end())
		return memo[curr_encode];
		
	int utility = terminal_test(state);
	
//	if(row == 3 && column == 3 && steps == 15){
//		cout<<"max "<<utility<<endl;
//		print_state();
//	}
	
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN){
		memo[curr_encode] = utility;	
		return utility;
	}
	
	int v = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)	
				continue;
			
			state[i][j] = X;
			curr_encode += 2*pow(3, (i * BOARD_COLUMN + j));
			
			v = max(v, min_value(i, j, alpha, beta, steps+1));
			
			state[i][j] = E;
			curr_encode -= 2*pow(3, (i * BOARD_COLUMN + j));
			
			if(v >= beta){
				if(steps >= DEPTH_LIMIT)
					memo[curr_encode] = v;	
				return v;
			}
			alpha = max(alpha, v);
		}
	}
	if(steps >= DEPTH_LIMIT)
		memo[curr_encode] = v;	
	return v;
}

