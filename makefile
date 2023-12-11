# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -std=c++11

# Header files
HDRS = Object.h Enemy.h Objective.h Room.h Player.h jsonParser.h MainEngine.h Map.h

# Source files
SRCS = Object.cpp Enemy.cpp Objective.cpp Room.cpp Player.cpp jsonParser.cpp MainEngine.cpp Map.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
