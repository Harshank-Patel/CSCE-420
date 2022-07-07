/*
 * Node.cpp
 *
 *  Created on: Mar 7, 2022
 *      Author: harshank
 */

#include "Node.h"

using namespace std;

Node::Node(int depth){
	this->depth = depth;
	this->mm_score = 0.0;
	this->parent = nullptr;
	this->final_state = nullptr;
}

Node::Node(State * state, int depth){
	this->mm_score = 0.00;
	this->depth = depth;
	this->game_state = state;
	this->final_state = nullptr;
	this->parent = nullptr;
}

string Node::print_node(){
	return this->game_state.print_state();
}

void Node::generate_children(char next_palyer){

	//Just count the number of spaces and then add those many children!
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->game_state.board[i][j] == '_'){
				State *stc = new State(&this->game_state);
				Node *temp = new Node(stc,this->depth+1);
				temp->parent = this;
				this->children.push_back(temp);
			}
		}
	}

	//Now we have all the blank spaces of children, so what we need to do is move the X/O into each of those locations!
	//cout <<"Size of the children : "<<this->children.size() <<endl;
	int iter = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->game_state.board[i][j] == '_'){
				this->children[iter]->game_state.board[i][j] = next_palyer;
				iter++;
			}
		}
	}
}

bool Node::termination_state(){
	if(this->remaining_moves() == 0 || this->someone_won('X') || this->someone_won('O')){
		return true;
	}
	return false;
}

void Node::maximum(char player, int &invocations, char OriginalPlayer){
//	cout <<"In Max Function!\n";
	this->generate_children(player);
	if(termination_state() == true){
		this->mm_score = this->won_pruning(OriginalPlayer);
//		cout <<"Depth of Termination State Is : "<<this->depth <<endl;
		return;
	}
	for(int i = 0; i < this->children.size(); i++){
		if(player == 'X'){
			invocations+=1;
			this->children[i]->minimum('O',invocations,OriginalPlayer);
		}
		else{
			invocations+=1;
			this->children[i]->minimum('X',invocations,OriginalPlayer);
		}
	}
	double maxVal = -999.999;
	for(int i = 0; i < this->children.size(); i++){
		if(this->children[i]->mm_score > maxVal){
			maxVal = this->children[i]->mm_score;
			this->final_state = &this->children[i]->game_state;
		}
	}
	this->mm_score = maxVal;
//	this->print_children();
}

void Node::minimum(char player, int &invocations, char OriginalPlayer){
//	cout <<"In Min Function!\n";
	this->generate_children(player);
	if(termination_state() == true){
		this->mm_score = this->won_pruning(OriginalPlayer);
//		cout <<"Depth of Termination State Is : "<<this->depth <<endl;
		return;
	}
	for(int i = 0; i < this->children.size(); i++){
		if(player == 'X'){
			invocations+=1;
			this->children[i]->maximum('O',invocations,OriginalPlayer);
		}
		else{
			invocations+=1;
			this->children[i]->maximum('X',invocations,OriginalPlayer);
		}
	}
	double minVal = 999.999;
	for(int i = 0; i < this->children.size(); i++){
		if(this->children[i]->mm_score < minVal){
			minVal = this->children[i]->mm_score;
			this->final_state = &this->children[i]->game_state;
		}
	}
	this->mm_score = minVal;
//	this->print_children();
}

State * Node::min_max_search(char player, int &invocations, char OriginalPlayer, bool pruning){
//	if(player == 'O'){
	if(!pruning){
		this->maximum(player, invocations, OriginalPlayer);
	}
	else{
		this->maximum(player, invocations, OriginalPlayer,INT_MIN,INT_MAX);
	}

//	}
//	else{
//		this->minimum(player, invocations, OriginalPlayer);
//	}
	return this->final_state;
}

void Node::choose(char player, int &invocations, char OriginalPlayer, bool pruning){
	//Now lets say choose 'O' was passed in, and now we have all the children of 'O' in all the locations
	this->min_max_search(player,invocations,OriginalPlayer,pruning);
}

void Node::move(char player, int row, int col){
	this->game_state.board[row][col] = player;
}

double Node::won(char player){
	if(this->game_state.board[0][0] == this->game_state.board[0][1] && this->game_state.board[0][1] == this->game_state.board[0][2]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in OO, O1, 02 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in OO, O1, 02 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}
	else if(this->game_state.board[1][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[1][2]){
		if(player == this->game_state.board[1][0]){
			//cout <<"Won in 1O, 11, 12 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 1O, 11, 12 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}
	else if(this->game_state.board[2][0] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[2][0]){
			//cout <<"Won in 2O, 21, 22 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 2O, 21, 22 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}



	else if(this->game_state.board[0][0] == this->game_state.board[2][0] && this->game_state.board[2][0] == this->game_state.board[1][0]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in 0O, 10, 20 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 0O, 10, 20 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}
	else if(this->game_state.board[0][1] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[1][1]){
		if(player == this->game_state.board[0][1]){
			//cout <<"Won in 01, 11, 21 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 01, 11, 21 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}
	else if(this->game_state.board[0][2] == this->game_state.board[1][2] && this->game_state.board[1][2] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][2]){
			//cout <<"Won in O2, 12, 12 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 02, 12, 22 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}


	else if(this->game_state.board[0][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in 0O, 11, 22 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 0O, 11, 22 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}

	else if(this->game_state.board[0][2] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][0]){
		if(player == this->game_state.board[0][2]){
			//cout <<"Won in 02, 11, 20 and by player "<<player <<"\n";
//			return 1-(0.1*this->depth);
			return 1;
		}
		else{
			//cout <<"Lost because other player won in 02, 11, 20 and by player "<<player <<"\n";
//			return -1-(0.1*this->depth);
			return -1;
		}
	}
	//cout <<"Stupid Draw here!!!\n";
	return 0;
}

void Node::print_children(){
	//cout <<"\n\nSTART OF PRINT_CHILDREN FUNCTION\n";
	cout <<"Depth is : "<<this->depth <<endl;
	cout <<"Parent is : \n" <<this->game_state.print_state() <<endl;
	cout <<"Children for this Parent Are : \n";
	for(int i = 0; i < this->children.size(); i++){
		cout <<this->children[i]->print_node();
		cout <<"MM_Value = "<<setprecision(5)<<this->children[i]->mm_score <<endl <<endl;
	}
	//cout <<"END OF PRINT_CHILDREN FUNCTION\n\n";
}

int Node::remaining_moves(){
	int temp = 0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(this->game_state.board[i][j] == '_'){
				temp++;
			}
		}
	}
	return temp;
}

bool Node::someone_won(char player){
	if(this->game_state.board[0][0] == this->game_state.board[0][1] && this->game_state.board[0][1] == this->game_state.board[0][2]){
		if(player == this->game_state.board[0][0]){
			return true;
		}
	}
	else if(this->game_state.board[1][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[1][2]){
		if(player == this->game_state.board[1][0]){
			return true;
		}
	}
	else if(this->game_state.board[2][0] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[2][0]){
			return true;
		}
	}



	else if(this->game_state.board[0][0] == this->game_state.board[2][0] && this->game_state.board[2][0] == this->game_state.board[1][0]){
		if(player == this->game_state.board[0][0]){
			return true;
		}
	}
	else if(this->game_state.board[0][1] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[1][1]){
		if(player == this->game_state.board[0][1]){
			return true;
		}
	}
	else if(this->game_state.board[0][2] == this->game_state.board[1][2] && this->game_state.board[1][2] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][2]){
			return true;
		}
	}


	else if(this->game_state.board[0][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][0]){
			return true;
		}
	}

	else if(this->game_state.board[0][2] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][0]){
		if(player == this->game_state.board[0][2]){
			return true;
		}
	}
	return false;
}

void Node::maximum(char player, int &invocations, char OriginalPlayer, double  alpha, double beta){
//	cout <<"In Max Function!\n";
	this->generate_children(player);
	if(termination_state() == true){
		this->mm_score = this->won_pruning(OriginalPlayer);
//		cout <<"Depth of Termination State Is : "<<this->depth <<endl;
		return;
	}
	double maxVal = -999.999;
	for(int i = 0; i < this->children.size(); i++){
		if(player == 'X'){
			invocations+=1;
			this->children[i]->minimum('O',invocations,OriginalPlayer,alpha,beta);
		}
		else{
			invocations+=1;
			this->children[i]->minimum('X',invocations,OriginalPlayer,alpha,beta);
		}

		if(this->children[i]->mm_score > maxVal){
			maxVal = this->children[i]->mm_score;
			this->final_state = &this->children[i]->game_state;
			alpha = max(alpha,maxVal);
		}

		if(maxVal >= beta){
			this->mm_score = maxVal;
			return;
		}
	}

	this->mm_score = maxVal;
//	this->print_children();
}

void Node::minimum(char player, int &invocations, char OriginalPlayer, double alpha, double beta){
	this->generate_children(player);
		if(termination_state() == true){
			this->mm_score = this->won_pruning(OriginalPlayer);
	//		cout <<"Depth of Termination State Is : "<<this->depth <<endl;
			return;
		}
		double minVal = 999.999;
		for(int i = 0; i < this->children.size(); i++){
			if(player == 'X'){
				invocations+=1;
				this->children[i]->maximum('O',invocations,OriginalPlayer,alpha,beta);
			}
			else{
				invocations+=1;
				this->children[i]->maximum('X',invocations,OriginalPlayer,alpha,beta);
			}
			if(this->children[i]->mm_score < minVal){
				minVal = this->children[i]->mm_score;
				this->final_state = &this->children[i]->game_state;
				alpha = min(alpha,minVal);
			}

			if(minVal <= alpha){
				this->mm_score = minVal;
				return;
			}
		}
		this->mm_score = minVal;
}

//pair <double,State*> Node::min_max_search_pruning(char player, int &invocations, char OriginalPlayer, bool maxFunc, double alpha, double beta){
//	this->generate_children(player);
//	if(this->termination_state() == true){
//		pair <double,State *> p;
//		p.first = this->won_pruning(OriginalPlayer);
//		p.second = &this->game_state;
//		return p;
//	}
//	if(maxFunc == true){
//		double BEST_VAL = INT_MIN;
//		State * BEST_NODE = &this->children[0]->game_state;
//		for(int i = 0; i < this->children.size(); i++){
//			double value;
//			State *value_node;
//			if(player == 'X'){
//				invocations+=1;
//				pair <double,State*> temp;
//				temp = this->children[i]->min_max_search_pruning('O',invocations,OriginalPlayer,false,alpha,beta);
//				value = temp.first;
//				value_node = temp.second;
//			}
//			else {
//				invocations+=1;
//				pair <double,State*> temp;
//				temp = this->children[i]->min_max_search_pruning('X',invocations,OriginalPlayer,false,alpha,beta);
//				value = temp.first;
//				value_node = temp.second;
//			}
//
//			BEST_VAL = max(value,BEST_VAL);
//
//			if(BEST_VAL == value){
//				BEST_NODE = value_node;
//				BEST_VAL = value;
//			}
//			alpha = std::max(alpha, value);
//			cout <<alpha <<" is alpha and bets is : "<<beta <<endl;
//			if(beta <= alpha){
//				cout <<"Pruned\n";
//				break;
//			}
//		}
//
//		pair<double,State *> p;
//		p.first = BEST_VAL;
//		p.second = BEST_NODE;
//		return p;
//
//	}
//	else{
//		double BEST_VAL = INT_MAX;
//		State * BEST_NODE = &this->children[0]->game_state;
//		for(int i = 0; i < this->children.size(); i++){
//			double value;
//			State *value_node;
//			if(player == 'X'){
//				invocations+=1;
//				pair <double,State*> temp;
//				temp = this->children[i]->min_max_search_pruning('O',invocations,OriginalPlayer,true,alpha,beta);
//				value = temp.first;
//				value_node = temp.second;
//			}
//			else {
//				invocations+=1;
//				pair <double,State*> temp;
//				temp = this->children[i]->min_max_search_pruning('X',invocations,OriginalPlayer,true,alpha,beta);
//				value = temp.first;
//				value_node = temp.second;
//			}
//			BEST_VAL = std::min(BEST_VAL,value);
//			if(BEST_VAL == value){
//				BEST_NODE = value_node;
//				BEST_VAL = value;
//			}
//			beta = std::min(beta, value);
//			if(beta <= alpha){
//				cout <<"Pruned\n";
//				break;
//			}
//		}
//		pair<double,State *> p;
//		p.first = BEST_VAL;
//		p.second = BEST_NODE;
//		return p;
//	}
//}

double Node::won_pruning(char player){
	if(this->game_state.board[0][0] == this->game_state.board[0][1] && this->game_state.board[0][1] == this->game_state.board[0][2]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in OO, O1, 02 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in OO, O1, 02 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}
	else if(this->game_state.board[1][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[1][2]){
		if(player == this->game_state.board[1][0]){
			//cout <<"Won in 1O, 11, 12 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 1O, 11, 12 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}
	else if(this->game_state.board[2][0] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[2][0]){
			//cout <<"Won in 2O, 21, 22 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 2O, 21, 22 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}



	else if(this->game_state.board[0][0] == this->game_state.board[2][0] && this->game_state.board[2][0] == this->game_state.board[1][0]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in 0O, 10, 20 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 0O, 10, 20 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}
	else if(this->game_state.board[0][1] == this->game_state.board[2][1] && this->game_state.board[2][1] == this->game_state.board[1][1]){
		if(player == this->game_state.board[0][1]){
			//cout <<"Won in 01, 11, 21 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 01, 11, 21 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}
	else if(this->game_state.board[0][2] == this->game_state.board[1][2] && this->game_state.board[1][2] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][2]){
			//cout <<"Won in O2, 12, 12 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 02, 12, 22 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}


	else if(this->game_state.board[0][0] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][2]){
		if(player == this->game_state.board[0][0]){
			//cout <<"Won in 0O, 11, 22 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 0O, 11, 22 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}

	else if(this->game_state.board[0][2] == this->game_state.board[1][1] && this->game_state.board[1][1] == this->game_state.board[2][0]){
		if(player == this->game_state.board[0][2]){
			//cout <<"Won in 02, 11, 20 and by player "<<player <<"\n";
			return 1-(0.1*this->depth);
//			return 1;
		}
		else{
			//cout <<"Lost because other player won in 02, 11, 20 and by player "<<player <<"\n";
			return -1-(0.1*this->depth);
//			return -1;
		}
	}
	return 0;
}
