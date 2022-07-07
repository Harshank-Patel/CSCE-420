/*
 * State.h
 *
 *  Created on: Mar 7, 2022
 *      Author: harshank
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

class State{
public:
	vector<vector<char>> board;

	State();
	State(State *);
	string print_state();
};

#endif /* STATE_H_ */
