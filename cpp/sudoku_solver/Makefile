sudoku: main.o sudoku.o
	g++ -g -Wall main.o sudoku.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -c -g -Wall -std=c++11 main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -c -g -Wall sudoku.cpp

