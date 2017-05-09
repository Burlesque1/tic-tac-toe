
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include "tic_tac_toe.h"
#include "player.h"

long long player::recurr_count = 0;

int main(int argc, char** argv) {
	while(1){
		cout<<"please select the difficulty level"<<endl;
		cout<<"1. easy\n2. medium\n3. hard\n"<<endl;
		
		int  level = 1;
		cin>>level;
		while(level > 3 || level <1){
			cout<<"Input error. Please re-select difficulty!"<<endl;
			cin>>level;
		}
		switch(level){
			case 1:cout<<"\nYou select ease level!\n"<<endl;;break;
			case 2:cout<<"\nYou select medium level!\n"<<endl;;break;
			case 3:cout<<"\nYou select hard level!\n"<<endl;;break;
		}
		cout<<"please select offensive or defensive position"<<endl;
		cout<<"0. offensive \n1. defensive\n"<<endl;
		
		bool  position = true;
		
		cin>>position; 
		
		tic_tac_toe t;
		
		player max_p(level);
		
		// human defend
		while(position){
			
			//t.show_info();
			t.print_board();
			
			time_t start = time(nullptr);
			
			// player max's turn
			max_p.get_last_move(t.return_last_move(), t.return_step());
			
			pair<int, int> move = max_p.return_move();
		
			bool if_over = t.next(move.first, move.second, X);
//			cout<<"if_over = "<<if_over<<endl;
			if(if_over)
				break;
			
			cout<<"\ntime "<<time(nullptr)-start<<"s "<<endl;
			max_p.print_info();
			
			
			// player min's turn
			t.print_board();
			cout<<"\nplease enter your move 'row column'"<<endl;
			int r = 0, c = 0;
			cin>>r>>c;
			if(r == 11 && c == 11)
				break;
			while(!t.check_input(r, c)){
				cout<<"input error r = "<<r<<" c = "<<c<<" please try another pair!"<<endl;
				cin>>r>>c;
			}
			pair<int, int> move2 = make_pair(r, c);
			if_over = t.next(move2.first, move2.second, O);
//			cout<<"if_over = "<<if_over<<endl;
			if(if_over)
				break;
		}
		
		// human offend
		while(!position){
			
			//t.show_info();
			t.print_board();
		
			// player min's turn
			cout<<"\nplease enter your move 'row column'"<<endl;
			int r = 0, c = 0;
			cin>>r>>c;
			if(r == 11 && c == 11)
				break;
			while(!t.check_input(r, c)){
				cout<<"input error r = "<<r<<" c = "<<c<<" please try another pair!"<<endl;
				cin>>r>>c;
			}
			pair<int, int> move2 = make_pair(r, c);
			bool if_over = t.next(move2.first, move2.second, O);
	//		cout<<"if_over = "<<if_over<<endl;
			if(if_over)
				break;
				
			// player max's turn
			time_t start = time(nullptr);
			t.print_board();
			max_p.get_last_move(t.return_last_move(), t.return_step());
			
			pair<int, int> move = max_p.return_move();
		
			if_over = t.next(move.first, move.second, X);
	//		cout<<"if_over = "<<if_over<<endl;
			if(if_over)
				break;
			
			cout<<"\ntime "<<time(nullptr)-start<<"s "<<endl;
			max_p.print_info();
		}
	}
	return 0;
}
