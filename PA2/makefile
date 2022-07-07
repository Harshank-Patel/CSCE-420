# *****************************************************
CC = g++
# ****************************************************
ttt: ttt.o State.o Node.o
	$(CC) -o ttt ttt.o State.o Node.o
Node.o: Node.cpp Node.h
	$(CC) -std=c++11 -c Node.cpp
ttt.o: ttt.cpp
	$(CC) -std=c++11 -c ttt.cpp
State.o: State.cpp State.h
	$(CC) -std=c++11 -c State.cpp
clean:
	rm *.o