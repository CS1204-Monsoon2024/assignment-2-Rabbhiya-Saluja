CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRCS = main.cpp HashTable.cpp
# Object files
OBJS = $(SRCS:.cpp=.o)
# Executable name
EXEC = hashtable_example

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
