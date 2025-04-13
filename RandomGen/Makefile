CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./include -I../MyArray/include -I/opt/homebrew/include

SRC = main.cpp
OBJ = main.o
BIN = main

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)

