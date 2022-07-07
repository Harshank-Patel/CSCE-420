//============================================================================
// Name        : PA4.cpp
// Author      : Harshank Patel
// Version     :
// Copyright   : Open Source
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Literals.h"
#include "Clause.h"

unordered_map <string,Literals*> map_of_literals;
bool uch_enabeled = true;
vector <Clause*> clauses;
bool assignment = false;
long long iter;


void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

void generate_clause(string input_line_read_from_file){
	string s = input_line_read_from_file;
	const char delim = ' ';
	vector<string> out;
	tokenize(s, delim, out);
	//TODO: Now implement the generate clause function!
	//Out vector has all the strings that are the Literals. Now we need to
	//convert that string to a Literal and add that to Clause class and also to the
	//map_of_literals map because we are keeping a map of all the literals!

	unordered_map <string,Literals*> temp_literal_map;

	for(int i = 0; i < out.size(); i++){

		if(out.at(i)[0] == '-'){
			//We know that its negative!
			//Now split the string into [1....n] and then basically add that to a map if it doesnt exist
			//as well as to the map_of_literals!
			unordered_map<string,Literals*>::iterator x = map_of_literals.find(out.at(i).substr(1));
			if(x != map_of_literals.end()){
				temp_literal_map[out.at(i)] = x->second;
			}
			else{
				Literals *newtempliteral = new Literals(out.at(i).substr(1));
				temp_literal_map[out.at(i)] = newtempliteral;
				map_of_literals[out.at(i).substr(1)] = newtempliteral;
//				cout <<out.at(i)<<endl;
//				cout <<"Here-2\n";
//				for(auto x: temp_literal_map){
//					cout <<"*****\n";
//					cout <<x.first <<endl;
//					cout <<x.second->print_literal();
//					cout <<"*****\n";
//				}
			}
		}
		else{
			//No Negation Symbol Present!
			unordered_map<string,Literals*>::iterator x = map_of_literals.find(out.at(i));
			if(x != map_of_literals.end()){
			    temp_literal_map[out.at(i)] = x->second;
			}
			else{
			    Literals *newtempliteral = new Literals(out.at(i));
			    temp_literal_map[out.at(i)] = newtempliteral;
			    map_of_literals[out.at(i)] = newtempliteral;
			}
		}
	}

	Clause *clause_temp = new Clause(temp_literal_map);
	clauses.push_back(clause_temp);
}

void read_file_function(string fileName){

	ifstream file(fileName);
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			if (line[0] == '#'){ // allow for comments (comment is entire line)
				continue;
			}
			if (line.find("#") != string::npos){ // allow for comments (comment is part of line)
				line = line.substr(0, line.find("#")); // trim comment out of line
			}
			if (line.size() == 0){ // allow for blank lines
				continue;
			}
			if (line.size() == 1 && line[0] == '\r'){ // allow for blank lines
				continue;
			}
			generate_clause(line);
		}
		file.close();
	}
	else{
		cout << "Error opening file." << endl;
		file.close();
		exit(1);
	}
	cout <<"Size of Clauses I read are : "<<clauses.size()<<"\n\n" <<endl;
}

string check_every_clause_in_clauses(vector <Clause*> clauses_here){
	for(auto x: clauses_here){
		if(x->evluate_clause() == "false"){
			return "false";
		}
		if(x->evluate_clause() == "unsatisfied"){
			return "unsatisfied";
		}
	}
	return "true";
}

Clause * find_unit_clause(vector<Clause*> *clauses_here){
	for(auto x: *clauses_here){
		if(x->isValidUnitClause_optimization() && x->evluate_clause_partial() == "false"){
//		if(x->isValidUnitClause()){
			return x;
		}
	}
	return nullptr;
}

string FIRST(unordered_map <string,Literals*> temp_map_of_literals){
	for(auto x: temp_map_of_literals){
		if(x.second->value == -1){
			return x.first;
		}
	}
	return "";
}

void print_model(vector <Clause*> *temp_clause,unordered_map <string,Literals*> *temp_map_of_literals){
	cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	for(auto x: *temp_map_of_literals){
		cout <<x.second->print_literal() <<endl;
	}
	for(auto x: *temp_clause){
		//x->print_clause();
	}
	cout <<"**********************************\n";
}


void uch_dpll(vector <Clause*> temp_clause,unordered_map <string,Literals*> temp_map_of_literals){
	iter++;
	//print_model(&temp_clause,&temp_map_of_literals);
	if(check_every_clause_in_clauses(temp_clause) == "true"){
		cout <<"Model : \n";
		for(auto x: temp_map_of_literals){
			cout <<x.second->print_literal() <<endl;
		}
		cout <<"\nIterations taken : "<<iter-1<<endl;
		cout <<"\n********************\nAbove Model is TRUE!\n********************\n";
		assignment = true;
		return;
	}

	if(check_every_clause_in_clauses(temp_clause) == "false"){
//		cout <<"Above Model is False!**************\n";
		return;
	}

	Clause *val;
	if(uch_enabeled){
		
		val = find_unit_clause(&temp_clause);
		
		//if I found a correct mode, I SHOULD just return it!
	}
	if(uch_enabeled && val != nullptr){
/****/
		int size_of_literals = val->data.size();
		if(size_of_literals == 1){

			for(auto x: val->data){
				//Now I have the x.first as the actual expected symbol like
				//-a and the Literal associated with it needs to be updated!

				if(x.second->value == -1 && x.first[0] == '-'){
					//That means I need to negate this Literal and assign it a value of False!
					//cout <<"Relaxed Single Model\n";
					//print_model(&temp_clause,&temp_map_of_literals);
					x.second->value = 0;
					//print_model(&temp_clause,&temp_map_of_literals);
					uch_dpll(temp_clause,temp_map_of_literals);
				}
				else if(x.second->value == -1 && x.first[0] != '-'){
					//cout <<"Relaxed Single Model\n";
					x.second->value = 1;
					//print_model(&temp_clause,&temp_map_of_literals);
					uch_dpll(temp_clause,temp_map_of_literals);
				}
			}
			//print_model(&temp_clause,&temp_map_of_literals);
			//Now call the recursive function since the assignment has been done!
		}
		else{
			//The Number of Literals are more than 1
			//Now I need to check if the clause is leaning towards the true or false side
			//And then do recursive calls
			//cout <<"2\n";
			string leaning_towards = val->evluate_clause_partial();
			if(leaning_towards == "false"){
				//Its leaning towards the False, so lets FORCE IT TO BE TRUE!
				for(auto x: val->data){
					//Now I have the x.first as the actual expected symbol like
					//-a and the Literal associated with it needs to be updated!
					if(x.second->value == -1 && x.first[0] == '-'){
						//That means I need to negate this Literal and assign it a value of False!
//						cout <<"Relaxed ONE OF MANY Models\n";
						//print_model(&temp_clause,&temp_map_of_literals);
						x.second->value = 0;
						//print_model(&temp_clause,&temp_map_of_literals);
						uch_dpll(temp_clause,temp_map_of_literals);
						x.second->value = -1;
					}
					else if(x.second->value == -1 && x.first[0] != '-'){
//						cout <<"Relaxed ONE OF MANY Models\n";
						//print_model(&temp_clause,&temp_map_of_literals);
						x.second->value = 1;
						//print_model(&temp_clause,&temp_map_of_literals);
						uch_dpll(temp_clause,temp_map_of_literals);
						x.second->value = -1;
					}
				}
			}
		}
































	}
	else{
		string P = FIRST(temp_map_of_literals);
		if(P != "" && assignment == false){
			if(assignment == false){
				temp_map_of_literals[P]->value = 1;
				uch_dpll(temp_clause,temp_map_of_literals);
			}
			if(assignment == false){
				temp_map_of_literals[P]->value = 0;
				uch_dpll(temp_clause,temp_map_of_literals);
			}
			temp_map_of_literals[P]->value = -1;
		}
	}
}

int main(int argc, char *argv[]){
	cout <<"\n\n\n";
	string filename = argv[1];
	if(argc > 2){
		//UCH flag should be disabled!
		uch_enabeled = false;
	}

	cout <<"1 = True, 0 = False, -1 = Incomplete\n\n\n\n";
	//Uncomment to run tests!!!
/*
	Clause * ans = generate_clause("-a -b c");
	if(ans->isUnitClause() == true){
		cout <<"Is Unit ? : True"<<endl;
	}
	else{
		cout <<"Is Unit ? : False"<<endl;
	}
	cout <<"Initial Evaluation : " <<ans->evluate_clause() <<endl;
	map_of_literals["a"]->value = 1;
	map_of_literals["b"]->value = 0;
	map_of_literals["c"]->value = 1;
	cout <<"Final Evaluation : " <<ans->evluate_clause() <<endl;

	read_file_function(filename);
	for(auto x: clauses){
		x->print_clause();
	}
*/

	//Load the contents of the file!
	read_file_function(filename);

	//Need a run DPLL function based on the flag and no flag!
	unordered_map <string,Literals*> temp_map_of_literals(map_of_literals);
	vector <Clause*> temp_clauses(clauses);

	uch_dpll(temp_clauses,temp_map_of_literals);
	if(assignment == false){
		cout <<"\nIterations taken : "<<iter-1<<endl;
		cout <<"\n********************\nGIVEN KB is NOT POSSIBLE!\n********************\n";
	}

	cout <<"\n\n\n";
	return 0;
}
