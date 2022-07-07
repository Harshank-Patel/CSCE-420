# *****************************************************
CC = g++
# ****************************************************
blocksworld: blocksworld.o State.o Node.o
	$(CC) -o blocksworld blocksworld.o State.o Node.o
Node.o: Node.cpp Node.h
	$(CC) -std=c++11 -c Node.cpp
blocksworld.o: blocksworld.cpp
	$(CC) -std=c++11 -c blocksworld.cpp
State.o: State.cpp State.h
	$(CC) -std=c++11 -c State.cpp
clean:
	rm *.o