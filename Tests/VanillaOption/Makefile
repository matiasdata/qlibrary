# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I../../include -MMD -MP

# Source files
SRC = main.cpp $(wildcard ../src/QLibrary/*.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
BIN = main

# Final binary build
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

# Compile each source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cleanup
clean:
	rm -f $(OBJ) $(DEP) $(BIN)

.PHONY: clean

# Include dependency files if they exist
-include $(DEP)