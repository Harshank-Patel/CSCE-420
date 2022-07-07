# *****************************************************
CC = g++
# ****************************************************
dpll: dpll.o Clause.o Literals.o
	$(CC) -o dpll dpll.o Clause.o Literals.o
Literals.o: Literals.cpp Literals.h
	$(CC) -std=c++11 -c Literals.cpp
dpll.o: dpll.cpp
	$(CC) -std=c++11 -c dpll.cpp
Clause.o: Clause.cpp Clause.h
	$(CC) -std=c++11 -c Clause.cpp
clean:
	rm *.o