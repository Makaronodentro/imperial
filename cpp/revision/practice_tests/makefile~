#makefile

FLAGS = -std=c++11 -g -Wall 

correct: ex6.o correct.o
	g++ $(FLAGS) ex6.o correct.o -o correct

ex6.o: ex6.cpp correct.h
	g++ $(FLAGS) -c $<
correct.o: correct.cpp correct.h
	g++ $(FLAGS) -c $<

maze: ex7.o maze.o
	g++ $(FLAGS) ex7.o maze.o -o maze

ex7.o: ex7.cpp maze.h
	g++ $(FLAGS) -c $<
maze.o: maze.cpp maze.h
	g++ $(FLAGS) -c $<

sonnet: ex8.o sonnet.o
	g++ $(FLAGS) ex8.o sonnet.o -o sonnet

ex8.o: ex8.cpp sonnet.h
	g++ $(FLAGS) -c $<
sonnet.o: sonnet.cpp sonnet.h
	g++ $(FLAGS) -c $<

run:
	./maze

clean:
	rm *.o
