#include <iostream>
#include <vector>

#define BOARD_ROW 2
#define BOARD_COLUMN 2

using namespace std; 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

enum entry {
		X, O, E
	};

class tic_tac_toe{

private:
	vector<vector<entry>> board;
	
	bool check_winner(int row, int column);
	
	int step_count;
	
	entry curr_player;
	
public:
	
	tic_tac_toe(){
		curr_player = X;
		step_count = 0; 
		board = vector<vector<entry>>(BOARD_ROW, vector<entry>(BOARD_COLUMN, E));
	} 
	
	bool next(int row, int column, entry en); 
	
	void show_info();
	
	void print_board();
	
	vector<vector<entry>> return_board();
	
	int return_step();
};

int tic_tac_toe::return_step(){
	return step_count;
}

vector<vector<entry>> tic_tac_toe::return_board(){
	return board;
}

bool tic_tac_toe::next(int row, int column, entry en){
//	if(board[row][column] != E){
//		cout<<"input error"<<endl;
//		return false;
//	}
	board[row][column] = en;
	++step_count;
	// 	check winner before return
	return check_winner(row, column);
}

bool tic_tac_toe::check_winner(int row, int column){
	if(step_count<BOARD_ROW)
		return false;
		
	int result = 0;
	
	string winner;
	if(board[row][column] == X)
		winner = "MAX";
	else
		winner = "MIN";
		
	// horizotal
	for(int i=row, j=0;j<BOARD_COLUMN;j++){
		if(board[i][j] != board[row][column]){
			result++;
			break;
		}
	}
	if(result == 0){
		cout<<"The winner is "<<winner<<endl;
		print_board();
		return true;
	}
	// vertical
	for(int i=0, j=column;i<BOARD_ROW;i++){
		if(board[i][j] != board[row][column]){
			result++;
			break;
		}
	}
	if(result == 1){
		cout<<"The winner is "<<winner<<endl;
		print_board();
		return true;
	}
	// diagnal
	if((row == 1 || row == 2) && (column == 1 || column == 2)){
		for(int i=0, j=0;i<BOARD_ROW && j<BOARD_COLUMN;i++, j++){
			if(board[i][j] != board[row][column]){
				result++;
				break;
			}
		}
		if(result == 2){
			cout<<"The winner is "<<winner<<endl;
			print_board();
			return true;
		}
		for(int i=0, j=BOARD_COLUMN - 1;i<BOARD_ROW && j>=0;i++, j--) {
			if(board[i][j] != board[row][column]){
				result++;
				break;
			}
		}
		if(result == 3){
			cout<<"The winner is "<<winner<<endl;
			print_board();
			return true;
		}
	}
	if(step_count == BOARD_ROW * BOARD_COLUMN)
		cout<<" draw "<<endl;
	return false;
} 

void tic_tac_toe::show_info(){
	
	cout<<"\n current step is "<<step_count<<endl;
	cout<<"\n next is "<<curr_player<<"'s turn"<<endl;
}

void tic_tac_toe::print_board(){
	for(auto b:board){
		for(auto bb:b){
			if(bb == E)
				cout<<"- ";	
			else
				cout<<bb<<" ";
		}
		cout<<endl;
	}
}

	
class player{

private:	
	pair<int, int> next_move;	
	
	// board state
	vector<vector<entry>> state;
	
	int curr_step;
	
	int checker(vector<vector<entry>> &state);
	
	// search
	void alpha_beta_search(vector<vector<entry>> &state);
	int max_value(vector<vector<entry>> &state, int &alpha, int &beta, int steps);
	int min_value(vector<vector<entry>> &state, int &alpha, int &beta, int steps);

public:	
	player(){
		next_move.first = 0;
		next_move.second = 0;
	} 
	
	void get_board(vector<vector<entry>> board, int step){
		curr_step = step;
		state = board;	// can be optimized 
		cout<<"\n-----"<<endl;
		for(auto s:state){
			for(auto ss:s){
				if(ss == E)
					cout<<"- ";	
				else
					cout<<ss<<" ";
			}
			cout<<endl;
		}
		cout<<"-----\n"<<endl;
	}
	
	// move
	pair<int, int> return_move();
};

pair<int, int> player::return_move(){	
	alpha_beta_search(state);
	return next_move;
}

void player::alpha_beta_search(vector<vector<entry>> &state){
	// if first step set X into middle
	;
	
	int value = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			int max_u = 1000, min_u = -1000;
			int v = max_value(state, min_u, max_u, curr_step);
			cout<<" v "<<v<<" i "<<i<<" j "<<j<<endl;
			if(v > value){
				value = v;
				next_move.first = i;
				next_move.second = j;
				cout<<"value = "<<value<<" i= "<<i<<" j= "<<j<<endl;
			}
		}
	}
}

int player::checker(vector<vector<entry>> &state){
	
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
			return state[i][0] == X ? 1000 : -1000;
	}
	
	// check columns
	for(int i=0;i<BOARD_COLUMN;i++){
		auto tmp = state[0][i];
		bool tag = true;
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != tmp){
				tag = false;
				break;
			}
		}
		if(tag)
			return state[0][i] == X ? 1000 : -1000;
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
		return state[0][0] == X ? 1000 : -1000;
	for(int i=0, j=BOARD_COLUMN-1;i<BOARD_ROW && j>=0;i++, j--){
		if(state[i][j] != state[0][BOARD_COLUMN-1]){
			tag = false;
			break;
		}
	}
	if(tag)
		return state[0][0] == X ? 1000 : -1000;
	return 0;
}

int player::max_value(vector<vector<entry>> &state, int &alpha, int &beta, int steps){
//		cout<<" max "<<steps<<endl;
	// check if board full
	if(steps == BOARD_ROW * BOARD_COLUMN){
		//call checker
		return checker(state);
	}
	
	int v = -1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			state[i][j] = X;	
			v = max(v, min_value(state, alpha, beta, ++steps));	
			state[i][j] = E;
			if(v >= beta)
				return v;
			alpha = max(v, alpha);
		}
	}
	return v;
}


int player::min_value(vector<vector<entry>> &state, int &alpha, int &beta, int steps){
//	cout<<" min "<<steps<<endl;
	// check if board full
	if(steps == BOARD_ROW * BOARD_COLUMN){
		//call checker
		return checker(state);
	}
	
	int v = 1000;
	for(int i=0;i<BOARD_ROW;i++){
		for(int j=0;j<BOARD_COLUMN;j++){
			if(state[i][j] != E)
				continue;
			state[i][j] = O;	
			v = min(v, max_value(state, alpha, beta, ++steps));	
			state[i][j] = E;
			if(v <= alpha)
				return v;
			beta = min(v, beta);
		}
	}
	return v;
}

int main(int argc, char** argv) {
	
	tic_tac_toe t;
	
	player max_p, min_p;
	
	int count=0;
	while(1){
		
		//t.show_info();
		t.print_board();
		
		// player max's turn
		max_p.get_board(t.return_board(), t.return_step());
		pair<int, int> move = max_p.return_move();
		bool if_over = t.next(move.first, move.second, X);
		if(if_over)
			break;
		
		// player min's turn
		t.print_board();
		int r = 0, c = 0;
		cin>>r>>c;
		pair<int, int> move2 = make_pair(r, c);
		if_over = t.next(move2.first, move2.second, O);
		if(if_over)
			break;
	}
	return 0;
}
