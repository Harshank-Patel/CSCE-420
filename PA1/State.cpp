#include "State.h"
#include "Node.h"


State::State(){}


string State::to_string(){
	string ret;
	for(int i = 0; i < stack.size(); i++){
		for(int j = 0; j < stack[i].size(); j++){
			ret+=stack[i][j];
		}
		ret+="|";
	}
	return ret;
}


void State::move_element(int from,int to){
	char c = stack[from].back();
	stack[from].pop_back();
	stack[to].push_back(c);
}


bool State::compareTo(State & other){
	if(this->to_string().compare(other.to_string()) == 0){
		return true;
	}
	return false;
}

void State::print_stack(){
	string ret;
	cout <<"[";
	for(int i = 0; i < stack.size(); i++){
		for(int j = 0; j < stack[i].size(); j++){
			cout <<stack[i][j] <<"";
		}
		if(i < stack.size()-1){
			cout <<"] [";
		}
	}
	cout <<"]   \n";
}

State::State(State &toCopy){

	for(int i = 0; i < toCopy.stack.size(); i++){
		vector <char> newVector;
		this->stack.push_back(newVector);
		for(int j = 0; j < toCopy.stack[i].size(); j++){
			this->stack[i].push_back(toCopy.stack[i][j]);
		}
	}

}
