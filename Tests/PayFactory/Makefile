# Compiler and flags
CXX = g++ -g
CXXFLAGS = -std=c++20 -Wall -I../../include

# Source files
SRC = main.cpp \
	../../src/QLibrary/PayoffFactory.cpp \
	../../src/QLibrary/Payoff.cpp \
	../../src/QLibrary/PayoffForward.cpp \
	../../src/QLibrary/PayoffStraddle.cpp \
	../../src/QLibrary/PayoffRegistration.cpp 

# Object files
OBJ = $(SRC:.cpp=.o)

# Output binary
BIN = main

# Default target
all: $(BIN)

# Link final binary
$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJ) $(BIN)

.PHONY: all clean