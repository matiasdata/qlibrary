# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -I./RandomGen/include -I./MyArray/include

# Targets
TARGET = randomgen
SRC = RandomGen/main.cpp
OBJ = $(SRC:.cpp=.o)

# Build rule
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f RandomGen/*.o $(TARGET)
