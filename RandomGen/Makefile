CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./include -I../MyArray/include

SRC = main.cpp
OBJ = main.o
BIN = randomgen

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(OBJ) $(BIN)