#include <iostream>
#include <vector>

using namespace std;

	enum entry {
		X, O, E
	};
//	
//class player{
//
//private:	
//	pair<int, int> next_move;	
//	
//	// board state
//	vector<vector<entry>> state;
//	
//	// search
//	void alpha_beta_search(vector<vector<entry>> &state);
//	int max_value(vector<vector<entry>> &state, int alpha, int beta);
//	int min_value(vector<vector<entry>> &state, int alpha, int beta);
//
//public:	
//	// move
//	pair<int, int> return_move();
//};
//
//pair<int, int> player::return_move(){	
//	return next_move;
//}
//
//void player::alpha_beta_search(vector<vector<entry>> &state){
//	// if first step set X into middle
//	;
//	
//	int value = -1000;
//	for(int i=0;i<4;i++){
//		for(int j=0;j<4;j++){
//			if(state[i][j] != E)
//				continue;
//			state[i][j] = X;
//			int v = max_value(state, 1000, -1000);
//			if(v > value){
//				value = v;
//				next_move.first = i;
//				next_move.second = j;
//			}
//			state[i][j] = E;
//		}
//	}
//}
//
//int player::max_value(vector<vector<entry>> &state, int alpha, int beta){
//	// check if board full
//	;
//	
//	int v = -1000;
//	for(int i=0;i<4;i++){
//		for(int j=0;j<4;j++){
//			if(state[i][j] != E)
//				continue;
//			state[i][j] = X;	
//			v = max(v, min_value(state, alpha, beta));
//			if(v >= beta)
//				return v;
//			alpha = max(v, alpha);	
//			state[i][j] = E;
//		}
//	}
//	return v;
//}
//
//
//int player::min_value(vector<vector<entry>> &state, int alpha, int beta){
//	// check if board full
//	;
//	
//	int v = 1000;
//	for(int i=0;i<4;i++){
//		for(int j=0;j<4;j++){
//			if(state[i][j] != E)
//				continue;
//			state[i][j] = X;	
//			v = min(v, max_value(state, alpha, beta));
//			if(v <= alpha)
//				return v;
//			beta = min(v, beta);	
//			state[i][j] = E;
//		}
//	}
//	return v;
//}
//
//

