OBJ=main.o enigma.o plugboard.o reflector.o rotor.o positions.o helper.o
EXE=enigma
CXX=g++
CPPFLAGS=-Wall -Wextra -Wcomment -g -MMD

$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<
	
.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ) $(OBJ:.o=.d)