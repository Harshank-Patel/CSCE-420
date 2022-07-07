#include <unordered_map>
#include <unordered_set>
#include <sys/wait.h>
#include <algorithm>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "State.h"
#include "Node.h"

using namespace std;

int num_stacks;
int num_blocks;
int num_possible_iterations;
int h_func = -1;

class Compare {
	public:
    	bool operator() (Node* a, Node* b) {
    		if(h_func == 2){

    			return (a->distance_combined+a->depth) > (b->distance_combined+b->depth);
    		}
    		else if(h_func == 3){

    			return (a->incorrect_blocks+a->depth) > (b->incorrect_blocks+b->depth);
    		}
    		else if(h_func == 4){

    			return (a->incorrect_blocks+a->distance_combined+a->depth) > (b->incorrect_blocks+b->distance_combined+b->depth);
    		}
    		return (a->incorrect_blocks+a->distance_combined+a->depth+a->min_block_moves__required) > (b->incorrect_blocks+b->distance_combined+b->depth+b->min_block_moves__required);
    	}
};

bool bfs_do = false;

long long int user_possible_iterations;

const string WHITESPACE = " \n\r\t\f\v";

string ltrim(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) {
    return rtrim(ltrim(s));
}

void split_string(string s, vector<string> &v){

	string temp = "";
	for(int i=0;i<s.length();++i){
		if(s[i] == ' '){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
	}
	v.push_back(trim(temp));
}

void read_from_file(string fileName, State &initial_state, State &final_state){
    // cout <<"Name of the file passed in is : " <<fileName <<endl;
    // cout <<"Opening a file" <<endl;

    ifstream myfile (fileName);
    string myline;
    if (myfile.is_open()){

        //First Line or Preamble
        vector <string> v;
        getline (myfile, myline);
        split_string(myline,v);
        num_stacks = stoi(v.at(0));
        num_blocks = stoi(v.at(1));
        num_possible_iterations = stoi(v.at(2));

        //>>>>>>> line read here
        getline (myfile, myline);

        //Now reading the given stacks for initial input (num_stacks times)
        for(int i = 0; i < num_stacks; i++){
            getline (myfile, myline);
            if(myline.length() == 0){
            	vector <char> new_vector;
            	initial_state.stack.push_back(new_vector);
            	continue;
            }
            for(int j = 0; j < myline.length(); j++){
            	if(initial_state.stack.size() < (i+1)){
            		vector <char> new_vector;
            		initial_state.stack.push_back(new_vector);
            	}
            	initial_state.stack.at(i).push_back(myline[j]);
            }
        }


        //>>>>>>> line read here
        getline (myfile, myline);

        //Now reading the given stacks for initial input (num_stacks times)
        for(int i = 0; i < num_stacks; i++){
            getline (myfile, myline);
            if(myline.length() == 0){
                vector <char> new_vector;
                final_state.stack.push_back(new_vector);
                continue;
            }
            for(int j = 0; j < myline.length(); j++){
                if(final_state.stack.size() < (i+1)){
                    vector <char> new_vector;
                    final_state.stack.push_back(new_vector);
                }
                final_state.stack.at(i).push_back(myline[j]);
            }
        }
    }
    else{
        cerr <<"Error opening the file, please check our workspace\n";
    }
    myfile.close();
}

Node * bfs_using_just_queue(Node *initial, Node *destination){

	if(initial->current->to_string() == destination->current->to_string()){
		return initial;
	}
	//Queue for the BFS
	queue < Node* > queue;

	//Set to keep the reached nodes in track!
	unordered_set <string> reached;

	//Insert the initial state's string into the hash-set since you already got here!
	reached.insert(initial->current->to_string());
	queue.push(initial);

	//While the queue is not empty!
	long long int iteration = 0;
	int maxQueueSize = 1;

	while(!queue.empty()){

		Node * front = queue.front();
		//cout <<"Depth of the node thats popped : "<<front->depth <<endl;
		queue.pop();

		if(front->current->to_string() == destination->current->to_string()){
			cout <<"     iter : "<<iteration <<",    ";
			cout <<"maxq : "<<maxQueueSize <<endl;
			cout <<"Depth of the FINAL node : "<<front->depth <<"\n\n\n"<<endl;
			return front;
		}
		iteration++;

		front->successors(destination->current);

		for (auto itr : front->childrens){

			if(itr->current->to_string() == destination->current->to_string()){
				cout <<"     iter : "<<iteration <<",    ";
				cout <<"maxq : "<<maxQueueSize <<",    ";
				//cout <<"Depth of the FINAL node : "<<front->depth <<"\n\n\n"<<endl;
				return itr;
			}
		    Node *temp = itr;
		    if(reached.find (temp->current->to_string()) == reached.end() ) {
		        reached.insert(temp->current->to_string());
		        queue.push(temp);

		    }
		}

		int sizeTemp = queue.size();
		maxQueueSize = std::max(maxQueueSize,sizeTemp);
	}
	return nullptr;
}

Node * A_Star(Node *initial, Node *destination){

	if(initial->current->to_string() == destination->current->to_string()){
		return initial;
	}


	//Queue for the A_Star
	std::priority_queue<Node *, std::vector<Node *>, Compare> queue;


	//Set to keep the reached nodes in track!
	unordered_set <string> reached;


	//Insert the initial state's string into the hash-set since you already got here!
	reached.insert(initial->current->to_string());
	queue.push(initial);


	//While the queue is not empty!
	long long int iteration = 0;
	int maxQueueSize = 1;
	int depth = 0;
	while(!queue.empty()){

		Node * front = queue.top();

		queue.pop();
//		front->current->print_stack();
//		cout <<"distance combined : "<<front->distance_combined <<",    ";
//		cout <<"depth : "<<front->depth <<",    ";
//		cout <<"iter : "<<iteration <<",    ";
//		cout <<"maxq : "<<maxQueueSize <<"    \n";
		if(front->current->to_string() == destination->current->to_string()){
			cout <<"\n\n  Max Queue Size : "<<maxQueueSize <<endl;
			cout <<" Iterations : "<<iteration <<endl;
			return front;
		}
		if(iteration+1 >= user_possible_iterations){
			cout <<"Crossed Max Iteration, sorry!\n";
			cout <<"\n\n";
			return nullptr;
		}
		iteration++;


		front->successors(destination->current);
		for (auto itr : front->childrens){
		    Node *temp = itr;
		    if(itr->current->to_string() == destination->current->to_string()){
		    	cout <<"\n\n  Max Queue Size : "<<maxQueueSize <<endl;
		    	cout <<"  Iterations : "<<iteration <<endl;
		    	return itr;
		    }
		    if(reached.find (temp->current->to_string()) == reached.end() ) {
		        reached.insert(temp->current->to_string());
		        queue.push(temp);

		    }
		}

		int sizeTemp = queue.size();
		maxQueueSize = std::max(maxQueueSize,sizeTemp);
	}


	return nullptr;
}

int main(int argc, char *argv[]){

    //Read from a file here
    if(argc < 2){
        cout <<"No arguments passed, refer the documentation to run this program "<<argc<<endl;
        exit(0);
    }
    int j;
    string fileName = "";
    user_possible_iterations = 1000000;
    while ((j = getopt(argc, argv, "f:i:h:b")) != -1) {
        switch (j) {
        	case 'f':
        		fileName = optarg;
        		break;
        	case 'b':
				bfs_do = true;
				break;
			case 'i':
				user_possible_iterations = std::stoi(optarg);
				break;
			case 'h':
				h_func = std::stoi(optarg);
				break;
        }
    }


    if(h_func == 4){
    	cout <<"Running heuristic with (incorrect blocks in the state) + (depth in the tree) + (sum of distance of each blocks currently from the destination state)" <<endl;
    }
    else if(h_func == 2){
    	cout <<"Running heuristic with (sum of distance of each blocks currently from the destination state) + (depth in the tree)" <<endl;
    }
    else if(h_func == 3){
    	cout <<"Running heuristic with (incorrect blocks in the state) + (depth in the tree)" <<endl;
    }
    else{
    	cout <<"Running DEFAULT heuristic which is using the (incorrect blocks in the state) + (sum of distance of each blocks currently from the destination state) + (min_estimated-moves)" <<endl;
    }


    State *initial_state = new State();
    State *final_state = new State();

    read_from_file(fileName,*initial_state,*final_state);


    //Generate initial's children!
    Node *initial_node = new Node(initial_state);
    Node *final_node = new Node(final_state);
    initial_node->update_stats(final_state);
    Node * found;
    int length;


    //********** Breath First Search Algorithm *************//
    if(bfs_do == true){
		cout <<"\n\n\n        BFS Results  \n\n";
		found = bfs_using_just_queue(initial_node,final_node);
		length = 0;
		if(found == nullptr){
			cout <<"Not Found using BFS!\n";
		}
		else{
			Node *curr = found;
			while(curr->current->to_string() != initial_state->to_string()){
				curr->current->print_stack();
				cout <<"Depth : "<<curr->depth <<endl <<endl;
				curr = curr->parent;
				length++;
			}
			curr->current->print_stack();
			cout <<"Depth : "<<curr->depth <<endl <<endl;
		}
		cout <<"     planLen for BFS : "<<length <<endl;
    }
    //******************************************************//



    //**************** A* Search Algorithm *****************//
	cout <<"\n\n\n         A* Results  \n\n";
	found = A_Star(initial_node,final_node);
	length = 0;
	if(found == nullptr){
		cout <<"Not Found using A_star Algorithm!\n";
	}
	else{
		cout <<"\n\n\nPriniting the planLen elements here : \n";
		Node *curr = found;
		while(curr->current->to_string() != initial_state->to_string()){
			curr->current->print_stack();
			cout <<"Distance of Each block from its Destination : " <<curr->distance_combined<<"    Min-Block need to move : "<<curr->min_block_moves__required <<"   Depth : "<<curr->depth <<"    Incorrect-Nodes : "<<curr->incorrect_blocks <<endl <<endl;
			curr = curr->parent;
			length++;
		}
		curr->current->print_stack();
		cout <<"Distance of Each block from its Destination : " <<curr->distance_combined<<"    Min-Block need to move : "<<curr->min_block_moves__required <<"   Depth : "<<curr->depth <<"    Incorrect-Nodes : "<<curr->incorrect_blocks <<endl <<endl;
	}
	cout <<"  planlen for A* : "<<length <<endl;
	cout <<"\n\n\n" <<endl;
    //******************************************************//

    return 0;
}
