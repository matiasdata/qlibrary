# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I../../include -MMD -MP

# Source files
SRC = main.cpp  ../src/QLibrary/RandomGen.cpp ../src/QLibrary/MyArray.cpp
OBJ = $(SRC:.cpp=.o)
BIN = main

# Final binary build
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

# Compile each source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(OBJ) $(BIN)

.PHONY: clean