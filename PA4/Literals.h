/*
 * Literals.h
 *
 *  Created on: Apr 11, 2022
 *      Author: harshank
 */

#ifndef LITERALS_H_
#define LITERALS_H_

#include <tuple>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iterator>
#include <iostream>
#include <unordered_map>

using namespace std;
/*
 *
 * -1 = Unassigned
 *  1 = True
 *  0 = False
 *
 * */
class Literals{

public:
	string name;
	int value;
	Literals(string);
	Literals(string,int);
	string print_literal();
};

#endif /* LITERALS_H_ */
