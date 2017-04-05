
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "tic_tac_toe.h"
#include "player.h"

long long player::recurr_count = 0;

int main(int argc, char** argv) {
	
	tic_tac_toe t;
	
	player max_p, min_p;
	
	while(1){
		
		
		//t.show_info();
		t.print_board();
		
		time_t start = time(nullptr);
		
		// player max's turn
//		max_p.get_board(t.return_board(), t.return_step());
		max_p.get_last_move(t.return_last_move(), t.return_step());
		
		pair<int, int> move = max_p.return_move();
	
		bool if_over = t.next(move.first, move.second, X);
		if(if_over)
			break;
		
		cout<<"\ntotal time "<<time(nullptr)-start<<endl;
//		max_p.test();
		cout<<"\ntotal recurrence count "<<max_p.show_recurr()<<"\n"<<endl;
		
		
		// player min's turn
//		t.show_info();
		t.print_board();
		int r = 0, c = 0;
		cin>>r>>c;
		while(!t.check_input(r, c)){
			cout<<"input error r = "<<r<<" c = "<<c<<" please try another pair!"<<endl;
			cin>>r>>c;
		}
		pair<int, int> move2 = make_pair(r, c);
		if_over = t.next(move2.first, move2.second, O);
		if(if_over)
			break;
	}
	return 0;
}
