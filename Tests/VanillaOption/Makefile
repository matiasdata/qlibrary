# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I../../include -MMD -MP -O3 -march=native -flto
LDFLAGS = -O3 -march=native -flto  # Link-time optimization flags

# Source files
SRC = main.cpp \
	../../src/QLibrary/RandomGen.cpp \
	../../src/QLibrary/MCStatistics.cpp \
	../../src/QLibrary/SimpleMC.cpp \
	../../src/QLibrary/Vanilla.cpp \
	../../src/QLibrary/Parameters.cpp \
	../../src/QLibrary/MyArray.cpp \
	../../src/QLibrary/Payoff.cpp
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