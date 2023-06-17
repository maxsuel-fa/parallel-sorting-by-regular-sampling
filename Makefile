# Compiler flags
CXX = mpicc
CXXFLAGS = -Wall -Wextra -Wpedantic
OMPFLAG = -fopenmp

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Compiling object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -c -o $@ $<

# Linking object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -o $(TARGET) $(OBJS)

# Cleaning object files and executable
clean:
	$(RM) $(OBJS) $(TARGET)

test:
	./$(TARGET) < input_file > test/output_file
	diff test/output_file test/expected_output_file

# Running the psrs
run:
	mpirun -np $(NP) $(TARGET) $(N)

