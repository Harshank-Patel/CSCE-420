#include "Node.h"


Node::Node(State *i) {
	this->min_block_moves__required = 0;
	this->distance_combined = 0.00;
	this->incorrect_blocks = 0;
	this->correct_blocks = 0;
	this->parent = nullptr;
	this->current = i;
	this->depth = 0;
}


Node::Node(State *i, Node *parent) {
	this->min_block_moves__required = 0;
	this->distance_combined = 0.00;
	this->incorrect_blocks = 0;
	this->correct_blocks = 0;
	this->parent = parent;
	this->current = i;
	this->depth = parent->depth+1;
}


Node::~Node() {
	this->childrens.clear();
}


void Node::successors(State *goal_state){
	int count_how_many_children_do_I_need = 0;
	for(int i = 0; i < this->current->stack.size(); i++){
		if(this->current->stack.at(i).size() != 0){
			count_how_many_children_do_I_need++;
		}
	}

	//Now make copies of those many children!
	vector <Node *> temp;

	for(int i = 0; i < count_how_many_children_do_I_need*2; i++){
		State *s = new State(*current);
		Node *node = new Node(s);
		node->parent = this;
		node->depth = this->depth+1;
		temp.push_back(node);
	}

	//Now make children!
	int first_non_zero_index_of_stack = 0;
	for(int i = 0; i < current->stack.size(); i++){
		if(current->stack[i].size() != 0){
			first_non_zero_index_of_stack = i;
			break;
		}
	}


	int item = 0;
	for(int i = 0; i < temp[0]->current->stack.size(); i++){
		for(int j = 0; j < temp[0]->current->stack.size(); j++){
			if(item == count_how_many_children_do_I_need*2){
				break;
			}
			if(i == j){
				continue;
			}
			if(temp[item]->current->stack[i].size() == 0){
				//Dont do anything!
			}else{
				temp[item]->current->move_element(i,j);
				item++;
			}
		}
	}

	for(int i = 0; i < temp.size(); i++){
		this->childrens.push_back(temp.at(i));
		temp.at(i)->update_stats(goal_state);
	}
}


void Node::update_stats(State *goal){

	unordered_map<char,string> map_current;

	int column_diff = 0;
	int row_diff = 0;

	for(int i = 0; i < this->current->stack.size(); i++){
		for(int j = 0; j < this->current->stack[i].size() ; j++){
			map_current[this->current->stack[i][j]] = std::to_string(i)+std::to_string(j);
		}
	}

	double total_distance = 0.00;
	int least_amount_moves = 0;
	for(int i = 0; i < goal->stack.size(); i++) {
		for(int j = 0; j < goal->stack[i].size() ; j++) {

			//Distance calculation
			char i_index = map_current.at(goal->stack[i][j])[0];
			char j_index = map_current.at(goal->stack[i][j])[1];

			int i_index_int = i_index - '0';
			int j_index_int = j_index - '0';

			//distance = SQRT [ (x2 − x1)^2 + (y2 − y1)^2 ]
			int x_diff = i_index_int - i;
			int y_diff = j_index_int - j;

			x_diff = x_diff * x_diff;
			y_diff = y_diff * y_diff;

			total_distance += sqrt(x_diff + y_diff);


			//Now do the counting of incorrect and correct blocks
			if(map_current.at(goal->stack[i][j]) == std::to_string(i)+std::to_string(j)) {
				this->correct_blocks++;
			}
			else {
				this->incorrect_blocks++;
			}

			//Now calculation the least-amount of moves required to get to final state!
			if(i_index_int != i && j_index_int != goal->stack[i].size()-1){
				//cout <<"Here-1!\n";
				//cout <<"To move "<<this->current->stack[i][j] <<" need 2 move"<<endl;
				least_amount_moves+=2;
			}
			else if(i_index_int != i && j_index_int == goal->stack[i].size()-1){
				//cout <<"Here-2!\n"<<i<<" "<<j<<endl;
//				cout <<"To move "<<this->current->stack[i][j] <<" need 1 move"<<endl;
				least_amount_moves+=1;
			}
			if(j_index_int != j){
//				cout <<"Here-3!\n";
				//cout <<"To move in upper area"<<current->stack[i][j] <<" needs 2 move"<<endl;
				least_amount_moves+=2;
			}
		}
	}
	this->min_block_moves__required = least_amount_moves;
	this->distance_combined = total_distance;
	//current->print_stack();
	//cout <<"Min Blocks Need to move : "<<min_block_moves__required<<endl;
	//cout <<"Distance Combined : "<<this->distance_combined <<endl;
}


Node* Node::predecessor(){
	return this->parent;
}
