CXX=g++-13
CFLAGS= -std=c++23
SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mks

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -f ./src/*.o $(EXECUTABLE)
