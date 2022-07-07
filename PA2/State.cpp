/*
 * State.cpp
 *
 *  Created on: Mar 7, 2022
 *      Author: harshank
 */

#include "State.h"

State::State(){
	//Do nothing!
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->board.size() < i+1){
				vector <char> temp;
				this->board.push_back(temp);
			}
			this->board[i].push_back('_');
		}
	}
}

State::State(State * other){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->board.size() < i+1){
				vector <char> temp;
				this->board.push_back(temp);
			}
			this->board[i].push_back(other->board[i][j]);
		}
	}
}

string State::print_state(){
	string ans = "";
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			ans += board[i][j];
			if(j < 2){
				ans += "|";
			}
		}
		ans += "\n";
	}
	return ans;
}
