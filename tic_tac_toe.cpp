#include "tic_tac_toe.h"

tic_tac_toe::tic_tac_toe(){
		
//		curr_player = X;		
		
		last_move = make_pair(-1, -1);
		
		step_count = 1; 		
		board = vector<vector<entry>>(BOARD_ROW, vector<entry>(BOARD_COLUMN, E));

//		step_count = 13; 
//		board =  {{X, X, O, O}, {X, X, O, O}, {E, X, X, E}, {O, E, O, E}};
		
	} 

int tic_tac_toe::return_step(){
	return step_count;
}

vector<vector<entry>> tic_tac_toe::return_board(){
	return board;
}

pair<int, int> tic_tac_toe::return_last_move(){
	return last_move;
}

bool tic_tac_toe::check_input(int row, int column){
	if(row<0 || column<0 || row>= BOARD_ROW || column>= BOARD_COLUMN || board[row][column] != E){
		cout<<"input error row = "<<row<<" column = "<<column<<endl;
		return false;
	}
	return true;
}

bool tic_tac_toe::next(int row, int column, entry en){
	
	board[row][column] = en;
	
	++step_count;
	
	last_move = make_pair(row, column);
	
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
		cout<<"\nThe winner is "<<winner<<endl;
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
		cout<<"\nThe winner is "<<winner<<endl;
		print_board();
		return true;
	}
	
	// diagnal
	if(((row == 1 || row == 2) && (column == 1 || column == 2)) || ((row == 0 || row == 3) && (column == 0 || column == 3))){
		for(int i=0, j=0;i<BOARD_ROW && j<BOARD_COLUMN;i++, j++){
			if(board[i][j] != board[row][column]){
				result++;
				break;
			}
		}
		if(result == 2){
			cout<<"\nThe winner is "<<winner<<endl;
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
			cout<<"\nThe winner is "<<winner<<endl;
			print_board();
			return true;
		}
	}
	
	if(step_count == BOARD_ROW * BOARD_COLUMN){
		cout<<" draw "<<endl;
		return true;
	}
	return false;
} 

void tic_tac_toe::show_info(){	
	cout<<"\n current step is "<<step_count<<endl;
	cout<<"\n next is "<<curr_player<<"'s turn"<<endl;
}

void tic_tac_toe::print_board(){
	cout<<"\ncurrent board:"<<endl;
	for(auto b:board){
		for(auto bb:b){
			if(bb == E)
				cout<<"- ";	
			else{
				string tmp;
				if(bb == X)
					tmp = "X";
				if(bb == O)
					tmp = "O";
				cout<<tmp<<" ";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}

