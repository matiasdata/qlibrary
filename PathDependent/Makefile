INCLUDES = -I../include
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

main: $(OBJECTS)
	g++ -std=c++20 $(OBJECTS) -o main

%.o: %.cpp
	g++ -std=c++20 $(INCLUDES) -c $< -o $@