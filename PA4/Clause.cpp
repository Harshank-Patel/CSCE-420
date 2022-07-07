/*
 * Clauses.cpp
 *
 *  Created on: Apr 11, 2022
 *      Author: harshank
 */

#include "Clause.h"

Clause::Clause(unordered_map<string, Literals *> data){
	for (auto x : data){
		this->data[x.first] = x.second;
	}
}

bool Clause::isUnitClause(){
	if(this->data.size() == 1){
		return true;
	}
	return false;
}

bool Clause::isValidUnitClause(){
	for(auto x : this->data){
		if(this->data.size() == 1 && x.second->value == -1){
			return true;
		}
	}
	return false;
}

bool Clause::isValidUnitClause_optimization(){
	//I got the size of the map and I need to iterate over the
	//literals and see HOW MANY are not satisfied
	for(auto x : this->data){
		if(this->data.size() == 1 && x.second->value == -1){
			return true;
		}
	}
	
	int size_of_clauses = this->data.size();

	int temp = 0;

	for(auto x : this->data){
		if(x.second->value != -1){
			temp++;
		}
	}
	//2+1 == 3
	if(temp == (size_of_clauses-1) && size_of_clauses > 1){
		return true;
	}
	return false;
}

string Clause::evluate_clause(){
	/*
	 *
	 * -1 = Unassigned
	 *  1 = True
	 *  0 = False
	 *
	 * */

	/* *
	 * unsatisfied = if the other Literals are not complete yet!
	 * false       = if any of the literals result into false!
	 * true        = if any of the literals have true in them!
	 * */

	for(auto x: this->data){
//		cout <<"Outside : "<<x.first <<endl;
		if(x.first[0] == '-'){
//			cout <<"Handling it differently because "<<x.first <<endl;
			//Handle it differently!
			if(x.second->value == -1){
				return "unsatisfied";
			}
			if(x.second->value == 1){
//				return "false";
			}
			if(x.second->value == 0){
				return "true";
			}
		}
		else{
//			cout <<"Handling it regular "<<x.first <<endl;
			if(x.second->value == -1){
				return "unsatisfied";
			}
			if(x.second->value == 0){
//				return "false";
			}
			if(x.second->value == 1){
				return "true";
			}
		}
	}
//	return "true";
	return "false";
}

void Clause::print_clause(){
	cout <<"Literals stored in these clauses are : \n";
	for(auto x: this->data){
		cout <<"(" <<x.first <<") ["<<x.second->print_literal() <<"] \n";
	}
	cout <<endl;
}

void Clause::relax_unit_clause(){
	for(auto x: this->data){
		//Now I have the x.first as the actual expected symbol like
		//-a and the Literal associated with it needs to be updated!
		if(x.second->value == -1 && x.first[0] == '-'){
			//That means I need to negate this Literal and assign it a value of False!
			x.second->value = 0;
		}
		else if(x.second->value == -1 && x.first[0] != '-'){
			x.second->value = 1;
		}
	}
//	this->print_clause();
}

string Clause::evluate_clause_partial(){
	for(auto x: this->data){
		if(x.first[0] == '-'){
			if(x.second->value == -1){
				continue;
			}
			if(x.second->value == 1){
			}
			if(x.second->value == 0){
				return "true";
			}
		}
		else{
			if(x.second->value == -1){
				continue;
			}
			if(x.second->value == 0){
			}
			if(x.second->value == 1){
				return "true";
			}
		}
	}
	return "false";
}
