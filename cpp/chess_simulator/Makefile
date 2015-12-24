OBJ=bin/ChessMain.o bin/ChessBoard.o bin/ChessPiece.o bin/King.o bin/Queen.o bin/Rook.o bin/Knight.o bin/Bishop.o bin/Pawn.o
TOBJ=bin/TestMain.o bin/ChessBoard.o bin/ChessPiece.o bin/King.o bin/Queen.o bin/Rook.o bin/Knight.o bin/Bishop.o bin/Pawn.o
EXE=chess
CXX=g++
CPPFLAGS=-Wall -Wextra -Wcomment -g -MMD -std=c++1y 

all: $(EXE) test

# chess executable
$(EXE): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(EXE)

# Extra Test Cases exec.
test: $(TOBJ)
	$(CXX) $(CPPFLAGS) $(TOBJ) -o $@

# Objects for ChessBoard, ChessMain and TestMain

bin/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $^ -o $@

# Objects for pieces

bin/%.o: pieces/%.cpp
	$(CXX) $(CPPFLAGS) -c $^ -o $@
      
.PHONY: clean

clean:
	rm -fR $(EXE) test bin