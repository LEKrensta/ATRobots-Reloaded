#include <iostream>
#include <string>

#include "types.hh"
#include "atrrfunc.hh"

using namespace std;

int main(int argc, char *argv[]){
	
	//loop variables
	int i, j, k, l, n, w;
	
	//turning off graphics
	graphix = false;
	
	if(matches > 0){
		for(i = 0; i < num_robots; i++){
			bout;
		}
	}

	if(matches > 1){
		cout << endl;
		cout << endl;

		cout << "Bout Complete! (" << matches << " matches)" << endl;

		k = 0;
		w = 0;

		for(i = 0; i < num_robots; i++){
			//with robot[i]^ do
			if(robot[i] -> wins = w){
				k++;
			}
			if(robot[i] -> wins > w){
				k = 1;
				n = i;
				w = robot[i] -> wins;
			}
		}
		cout << "Robot           Wins  Matches  Kills  Deaths    Shots" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		for(i = 0; i < num_robots; i++){
			cout << addfront(cstr(i+1), 2) << " - " << addrear(robot[i] -> fn, 8) << 
			addfront(cstr(robot[i] -> wins), 7) << addfront(cstr(robot[i] -> trials), 8) << 
			addfront(cstr(robot[i] -> kills), 8) << addfront(cstr(robot[i] -> deaths), 8) <<
			addfront(cstr(robot[i] -> shots_fired), 9);
		}
		cout << endl;

		if(k == 1){
			cout << "Robot #" << n+1 << *robot[n] -> fn << "wins the bout! (Score: " << w << "/" << matches << ")" << endl;
		}
		else{
			cout << "There is no clear victor!" << endl;
		}
	}
}

void bout(){
	int i, j, k, n;
	char c;
	long timer;

	played++;
	//init_bout();
	bout_over = false;

	if(step_mode = 0){
		step_loop = false;
	}
	else{
		step_loop = true;
	}
	step_count = -1;

	if(graphix && (step_mode > 0)){
		for(i = 0; i < num_robots; i++){
			draw_robot(i);
		}
	}

	do{
		game_cycle++;
		for(i = 0; i < num_robots; i++){
			if(robot[i] -> armor > 0){
				do_robot(i);
			}
		}
		for(i = 0; i < max_missiles; i++){
			if(missile[i].a > 0){
				do_missile(i);
			}
		}
		for(i = 0; i < num_robots; i++){
			for(k = 0; k < max_mines; k++){
				if(robot[i] -> mine[k].yield > 0){
					do_mine(i, k);
				}
			}
		}
		/*
		if(graphix && timing){
			time_delay(game_delay);
		}
		if(keypressed){
			c = uCase(readkey);
		}
		else{
		//	c = #255;
		}
		*/

		switch(c){
			case 'X':
			if(!robot[0] -> is_locked){
				if(!graphix){
					toggle_graphix();
				}
				if(robot[0] -> armor > 0){
					if(temp_mode > 0){
						step_mode = temp_mode;
					}
					else{
						step_mode = 1;
					}
					step_count = -1;
					//init_debug_window();
				}
			}
			//ARTIFACT
			case '+': case '=':
			if(game_delay < 100){
				switch(game_delay){
					case 000 ... 004: game_delay = 005;
					case 005 ... 009: game_delay = 010;
					case 010 ... 014: game_delay = 015;
					case 015 ... 019: game_delay = 020;
					case 020 ... 029: game_delay = 030;
					case 030 ... 039: game_delay = 040;
					case 040 ... 049: game_delay = 050;
					case 050 ... 059: game_delay = 060;
					case 060 ... 079: game_delay = 075;
					case 075 ... 100: game_delay = 100;
				}
			}
			case '-': case '_':
			if(game_delay > 0){
				switch(game_delay){
					case 000 ... 005: game_delay = 000;
					case 006 ... 010: game_delay = 005;
					case 011 ... 015: game_delay = 010;
					case 016 ... 020: game_delay = 015;
					case 021 ... 030: game_delay = 020;
					case 031 ... 040: game_delay = 030;
					case 041 ... 050: game_delay = 040;
					case 051 ... 060: game_delay = 050;
					case 061 ... 075: game_delay = 060;
					case 076 ... 100: game_delay = 075;
				}
			}
			case 'G': toggle_graphix();
			default: process_keypress(c);
		}
		//flushkey();

		if(game_delay < 0){
			game_delay = 0;
		}
		if(game_delay > 100){
			game_delay = 100;
		}

		switch(game_delay){
			case 000 ... 001: k = 100;
			case 002 ... 005: k = 50;
			case 006 ... 010: k = 25;
			case 011 ... 025: k = 20;
			case 026 ... 040: k = 10;
			case 041 ... 070: k = 5;
			case 071 ... 32787: k = 1;
			default: k = 10;
		}
		
		if(!graphix){
			k = 100;
		}
		
	}while(/* gameover() || */ bout_over);

}

string operand (int n, int m)
{
    string s;
    s = cstr(n);
    switch(m & 7)
    {
        case 1: s = "@" + s; break;
        case 2: s = ":" + s; break;
        case 3: s = "$" + s; break;
        case 4: s = "!" + s; break;
        default: s = cstr(n); break;
    }
    if((m & 8) > 0)
    {
        s = "[" + s + "]";
    }
    return s;
}


string mnemonic (int n, int m)
{
	string s;
	s = cstr(n);
	if(m == 0)
	{
		switch(n)
		{
			case 0:  s = "NOP"; break;
   			case 1:  s = "ADD"; break;
   			case 2:  s = "SUB"; break;
   			case 3:  s = "OR"; break;
 		 	case 4:  s = "AND"; break;
   			case 5:  s = "XOR"; break;
   			case 6:  s = "NOT"; break;
			case 7:  s = "MPY"; break;
        	case 8:  s = "DIV"; break;
   			case 9:  s = "MOD"; break;
      		case 10:  s = "RET"; break; 
   			case 11:  s = "CALL"; break; 
			case 12:  s = "JMP"; break;
   			case 13:  s = "JLS"; break;
   			case 14:  s = "JGR"; break;
   			case 15:  s = "JNE"; break;
			case 16:  s = "JE"; break;
   			case 17:  s = "SWAP"; break;
   			case 18:  s = "DO"; break;
   			case 19:  s = "LOOP"; break;
			case 20:  s = "CMP"; break;
   			case 21:  s = "TEST"; break;
   			case 22:  s = "MOV"; break;
   			case 23:  s = "LOC"; break;
			case 24:  s = "GET"; break;
         	case 25:  s = "PUT"; break;
   			case 26:  s = "INT"; break;
   			case 27:  s = "IPO"; break;
			case 28:  s = "OPO"; break;
   			case 29:  s = "DELAY"; break;
   			case 30:  s = "PUSH"; break;
   			case 31:  s = "POP"; break;
			case 32:  s = "ERR"; break;
   			case 33:  s = "INC"; break;
   			case 34:  s = "DEC"; break;
   			case 35:  s = "SHL"; break;
			case 36:  s = "SHR"; break;
  	 	   	case 37:  s = "ROL"; break;
 			case 38:  s = "ROR"; break;
         	case 39:  s = "JZ"; break;
  			case 40:  s = "JNZ"; break;
   			case 41:  s = "JGE"; break;
   			case 42:  s = "JLE"; break;
  		 	case 43:  s = "SAL"; break;
   			case 44:  s = "SAR"; break;
   			case 45:  s = "NEG"; break;
   			case 46:  s = "JTL"; break;
   			default:  s = "XXX"; break;
		}
	}
	else
	{
		s = operand(n,m);
	}
	return s;
}

void process_keypress(char c){
	return;
}

/*
----- GRAPHICS FUNCTIONS ----
*/

void graph_mode(bool on){
	return;
}

void toggle_graphix(){
	graph_mode(!graphix);
	if(!graphix){
		cout << "Match " << played << "/" << matches << ", Battle in progress..." << endl;
	}
	return;
}

/* 
------ ROBOT FUNCTIONS -----
Empty and return void in order to create sitting duck
*/

void do_mine(int n, int m){
	return;
}

void do_missile(int n){
	return;
}

void do_robot(int n){
	return;
}

void draw_robot(int n){
	return;
}