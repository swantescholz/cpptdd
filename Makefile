EXEC=application
SRC=$(wildcard src/*.cpp src/*/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)
OBJ=$(SRC:.cpp=.o)
INC=
LIBS=

CC=g++
CCOPTS=-std=c++11 -c -Wall -pthread

all: $(EXEC)

$(EXEC): $(OBJ)
	$(LINK.o) $^ -o $@ $(LIBS)

.cpp.o :
	$(CC) $(CCOPTS) $(INC) -c $< -o $@

clean:
	rm $(EXEC) $(OBJ)


#Special symbols used:
#$^ - is all the dependencies (in this case =$(OBJECTS) )
#$@ - is the result name (in this case =$(EXECUTABLE) )
