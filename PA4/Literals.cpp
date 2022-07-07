/*
 * Literals.h
 *
 *  Created on: Apr 11, 2022
 *      Author: harshank
 */

#include "Literals.h"

Literals::Literals(string name){
	this->name = name;
	this->value = -1;
}

Literals::Literals(string name, int value){
	this->name = name;
	this->value = value;
}

string Literals::print_literal(){
	string temp = "";
	temp += this->name;
	temp += " : ";
	temp += to_string(this->value);
	return temp;
}
