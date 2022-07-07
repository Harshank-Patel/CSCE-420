#ifndef NODE_H_
#define NODE_H_

#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#include "State.h"

using namespace std;

class Node {
public:

	///////////////////////
	Node * parent;
	vector<Node *> childrens;
	State * current;

	int correct_blocks;
	int incorrect_blocks;
	double distance_combined;
	int depth;
	int min_block_moves__required;

	/*********************/
	Node(State *);
	Node(State *, Node *);
	virtual ~Node();


	/*********************/
	void successors(State *);   //A function to generate its children/permutations!
	void update_stats(State *);
	Node* predecessor();
};

#endif /* NODE_H_ */
