/*
 * Clauses.h
 *
 *  Created on: Apr 11, 2022
 *      Author: harshank
 */

#ifndef CLAUSE_H_
#define CLAUSE_H_


#include "Literals.h"

class Clause{
public:

	unordered_map<string, Literals *> data;

	bool isUnitClause();
	bool isValidUnitClause();
	bool isValidUnitClause_optimization();
	void print_clause();
	string evluate_clause();
	string evluate_clause_partial();

	Clause(unordered_map<string, Literals *>);
	void relax_unit_clause();
};


#endif /* CLAUSE_H_ */
