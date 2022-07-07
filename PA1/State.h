#ifndef STATE_H_
#define STATE_H_

#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <array>

using namespace std;

class State {
public:
	/*********************/
	vector < vector< char > > stack;

	/*********************/
	State();
	State(State &);
	void print_stack();
	void move_element(int,int);
	string to_string();
	bool compareTo(State &);
};



#endif /* STATE_H_ */
