#ifndef NODE_H_
#define NODE_H_

#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <limits>
#include "State.h"

using namespace std;

class Node{
public:
	int depth;
	Node *parent;
	double mm_score;
	State game_state;
	State *final_state;
	vector <Node *> children;

	Node(int);
	double won(char);
	void choose(char,int &, char, bool);
	void maximum(char, int &, char);
	void minimum(char, int &, char);
	string print_node();
	void print_children();
	int remaining_moves();
	bool someone_won(char);
	void move(char,int,int);
	Node(State * state,int);
	bool termination_state();
	void generate_children(char);
	State * min_max_search(char,int &, char, bool);




	/*
	 * Alpha-Beta Pruning Methods Start Here!
	 * */
//	pair <double,State*> min_max_search_pruning(char, int&, char, bool, double, double);

	double won_pruning(char);

	void maximum(char, int &, char, double, double);
	void minimum(char, int &, char, double, double);

	//double won_pruning(char);
//	void maximum_pruning(char, int &, char, double &, double &);
//	void minimum_pruning(char, int &, char, double &, double &);
//	void min_max_search_pruning(char, int&, char, bool, double &, double &);

};

#endif /* NODE_H_ */
