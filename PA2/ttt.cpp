//============================================================================
// Name        : PA2.cpp
// Author      : Harshank
// Version     :
// Copyright   : Open Source
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include "State.h"
#include "Node.h"

using namespace std;

std::vector<std::string> string_split(const std::string& str) {
	std::vector<std::string> result;
	std::istringstream iss(str);
	for (std::string s; iss >> s; )
		result.push_back(s);
	return result;
}


int main() {
	//
	bool pruning = false;
	//
	State *s = new State();
	Node *n = new Node(s,0);
	n->game_state.board[0][0] = 'X';
	n->game_state.board[0][1] = 'O';
	int invocations=0;

	cout <<"\n\nHello World!\n";
	cout <<"Hi, I am Alexe. I am powered by AI and I want to play Tic-Tac-Toe : \n\n";
	string input;

	while(true){
		if(pruning == false){
			cout <<"Pruning Default Off\n\n";
		}
		else{
			cout <<"\n\nPruning IS ON\n";
			cout <<"To Turn it off, please type \"pruning\"\n\n";
		}
		std::cout << "Please choose the following options:\n* TTT or ttt - To start a game\n* pruning or P or PRUNING - To turn on/off pruning\n* move [X] [A] [0] - To move X into A 0 location\n* choose [X] - Let Algorithm pick the X\n* q or quit - To exit the program\n\n ->  ";
		std::getline (cin,input);
		if(input == "quit" || input == "q"){
			break;
		}
		if(input == "ttt" || input == "TTT"){
			cout <<"\nStarting New Game\n\n\n";
			delete n;
			n = new Node(s,1);

//			n->game_state.board[0][0] = 'X';
//			n->game_state.board[0][1] = 'O';
//			n->game_state.board[0][2] = 'X';


//			n->game_state.board[2][0] = 'O';
//			n->game_state.board[1][1] = 'X';
//			n->game_state.board[2][2] = 'O';

//			n->game_state.board[2][2] = 'O';

			cout <<n->print_node() <<endl;
		}
		else if (input == "pruning" || input == "P" || input == "PRUNING"){
			pruning = !pruning;

			delete n;
			n = new Node(s,1);
		}
		else if (string_split(input).size() == 2){
			//Its a choose call!
			if(pruning){
				n->choose(string_split(input)[1][0],invocations,string_split(input)[1][0],true);
				n->game_state = n->final_state;
			}
			else{
				n->choose(string_split(input)[1][0],invocations,string_split(input)[1][0],false);
				n->game_state = n->final_state;
			}
			cout <<"\n" <<n->print_node()<<endl;
			n->children.clear();
			if(n->someone_won('O') == true){
				cout <<"Total Iterations : "<<invocations <<endl;
				invocations = 0;
				cout <<"O wins!\n\n";
				break;
			}
			if(n->someone_won('X') == true){
				cout <<"Total Iterations : "<<invocations <<endl;
				invocations = 0;
				cout <<"X wins!\n\n";
				break;
			}
			if(n->remaining_moves() == 0){
				cout <<"Total Iterations : "<<invocations <<endl;
				invocations = 0;
				cout <<"Tie *******!\n\n";
				cout <<"Restart program if you want to play again!\n";
				break;
			}
			cout <<"Total Iterations : "<<invocations <<endl;
			invocations = 0;
		}
		else if (string_split(input).size() == 4){
			//Its a move call!
			char player = string_split(input)[1][0];
			char row = string_split(input)[2][0];
			int row_int = -1;
			if(row == 'A'){
				row_int = 0;
			}
			if(row == 'B'){
				row_int = 1;
			}
			if(row == 'C'){
				row_int = 2;
			}
			char col = string_split(input)[3][0];
			n->move(player, row_int, col-'0');
			cout <<"\n" <<n->print_node()<<endl;
			if(n->someone_won('O') == true){
				cout <<"O wins!\n\n";
				break;
			}
			if(n->someone_won('X') == true){
				cout <<"X wins!\n\n";
			}
			if(n->remaining_moves() == 0){
				cout <<"Tie *******!\n\n";
				cout <<"Restart program if you want to play again!\n";
				break;
			}
			if(n->someone_won('O') == true){
				cout <<"O wins!\n\n";
				break;
			}
			if(n->someone_won('X') == true){
				cout <<"X wins!\n\n";
			}
			if(n->remaining_moves() == 0){
				cout <<"Tie *******!\n\n";
				cout <<"Restart program if you want to play again!\n";
				break;
			}
			cout <<"Total Iterations : "<<invocations <<endl;
			invocations = 0;
		}
	}
	return 0;
}
