#include "player.h"

player::player(){
	
//	state = {{X, X, X, O}, {X, X, O, E}, {O, X, E, E}, {O, O, O, E}};
	
	state = vector<vector<entry>>(BOARD_ROW, vector<entry>(BOARD_COLUMN, E));
	
	curr_encode = 0;
		
	depth = 0;
	
	max_prune = 0;
	
	min_prune = 0;
	
	next_move.first = -1;
	
	next_move.second = -1;
	
	memo = unordered_map<long long, int>();
}

void player::print_info(){
	
	cout<<"(1) no cutoff occurred"<<endl;
	
	cout<<"(2) maximum depth reached: "<<depth<<endl;
	
	cout<<"(3) total number of nodes generated: "<<recurr_count<<endl;
	
	cout<<"(4) number of times pruning occurred(max): "<<max_prune<<endl;
	
	cout<<"(5) number of times pruning occurred(min): "<<min_prune<<endl;
	
	cout<<"memo size: "<<memo.size()<<endl;
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
//	cout<<"curr_encode & 14408200 == 14408200 "<<(curr_encode & 14408200 == 14408200)<<endl;
//	cout<<"(curr_encode - 551880) ^ 551880 "<<((curr_encode - 551880) ^ 551880)<<endl;
//	cout<<"(curr_encode - 28816400) ^ 28816400 "<<((curr_encode - 28816400) ^ 28816400) <<endl;
//	cout<<"(curr_encode - 1103760) ^ 1103760 "<<((curr_encode - 1103760) ^ 1103760) <<endl;
	 
	// diagnal 
//	if((curr_encode >= 14408200 && (curr_encode & 14408200) == 14408200) || (curr_encode >= 551880 && (curr_encode & 551880) == 551880))
//		{
//			return -1000;
//		}
//	
//	if((curr_encode >= 28816400 && (curr_encode & 28816400) == 28816400) || (curr_encode >= 1103760 && (curr_encode & 1103760) == 1103760))
//		return 1000;
//	
//	// row	
//	for(int i = 1, p = 40;i < BOARD_ROW;i++, p *= 81){
//		if(curr_encode < p)
//			continue;
//		if((curr_encode & p) == p)
//			{
//				cout<<curr_encode<<" d "<<p<<endl;
//				exit(0);
//				return -1000;
//			}
//		if((curr_encode & 2 * p) == 2 * p)
//			return 1000;
//	}
//	
//	// column
//	for(int i = 1, p = 538084;i < BOARD_COLUMN;i++, p *= 3){
//		if(curr_encode < p)
//			continue;
//		if((curr_encode & p) == p)
//			return -1000;
//		if((curr_encode & 2 * p) == 2 * p)
//			return 1000;
//	}
//	
//	return 0;
	
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
				
			int curr_dep = 1;
			
			if(next_move.first == -1){
				next_move.first = i;
				next_move.second = j;
			}
			state[i][j] = X;
			
			curr_encode += 2*pow(3, (i * BOARD_COLUMN + j));
			
			int max_u = 1000, min_u = -1000;
			
			time_t start = time(nullptr);
				
			int v = min_value(i, j, min_u, max_u, curr_step+1, curr_dep);
			
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

int player::min_value(int row, int column, int alpha, int beta, int steps, int &curr_dep){

	recurr_count++;
	
	if(memo.find(curr_encode) != memo.end()){
		depth = max(curr_dep + 1, depth);
		return memo[curr_encode];
	}
	int utility = terminal_test(state);
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN){
		memo[curr_encode] = utility;
		depth = max(curr_dep + 1, depth);	
		return utility;
	}
	
	curr_dep++;
	int v = 1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			
			state[i][j] = O;
			curr_encode += pow(3, (i * BOARD_COLUMN + j));
			
			v = min(v, max_value(i, j, alpha, beta, steps+1, curr_dep));
			
			state[i][j] = E;
			
			curr_encode -= pow(3, (i * BOARD_COLUMN + j));
			
			if(v <= alpha){
				if(steps >= DEPTH_LIMIT)
					memo[curr_encode] = v;
				curr_dep--;
				min_prune++;
				return v;
			}
			beta = min(v, beta);
		}		
	}
	if(steps >= DEPTH_LIMIT)
		memo[curr_encode] = v;	
	curr_dep--;
	return v;
}

int player::max_value(int row, int column, int alpha, int beta, int steps, int &curr_dep){
	
	recurr_count++;
	
	if(memo.find(curr_encode) != memo.end()){
		depth = max(curr_dep + 1, depth);
		return memo[curr_encode];
	}
		
	int utility = terminal_test(state);
	if(utility != 0 || steps == BOARD_ROW * BOARD_COLUMN){
		memo[curr_encode] = utility;	
		depth = max(curr_dep + 1, depth);
		return utility;
	}
	
	curr_dep++;
	int v = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)	
				continue;
			
			state[i][j] = X;
			curr_encode += 2*pow(3, (i * BOARD_COLUMN + j));
			
			v = max(v, min_value(i, j, alpha, beta, steps+1, curr_dep));
			
			state[i][j] = E;
			curr_encode -= 2*pow(3, (i * BOARD_COLUMN + j));
			
			if(v >= beta){
				if(steps >= DEPTH_LIMIT)
					memo[curr_encode] = v;	
				curr_dep--;
				max_prune++;
				return v;
			}
			alpha = max(alpha, v);
		}
	}
	if(steps >= DEPTH_LIMIT)
		memo[curr_encode] = v;
	curr_dep--;	
	return v;
}

