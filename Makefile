# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -lgtest -lgtest_main -pthread

# Target executable
TARGET = BigIntegerTest.out

# Source files
SRCS = BigInteger.cpp BigIntegerTest.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean