# Specify the compiler
CXX = g++

# Specify compiler flags
CXXFLAGS = -Wall -std=c++17

# Specify the linker flags
# Add `-lsqlite3` to link the SQLite3 library
LDFLAGS = -lsqlite3 

# Specify the target file
TARGET = car_app

# Specify the source files
SOURCES = src/VehicleConfiguration.cpp src/Database.cpp main.cpp src/Menu.cpp lib/Exceptions.cpp lib/common.c

# Specify the object files
OBJECTS = $(SOURCES:.cpp=.o) $(SOURCES:.c=.o)

all: $(TARGET)

# Test files
TEST_SOURCES = tests/run-tests.cpp src/Database.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)
TEST_TARGET = run-tests

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

# A pattern rule to create ".o" object files from ".cpp" source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# A pattern rule to create ".o" object files from ".c" source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJECTS) $(LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Add a clean target
clean:
	rm -f $(TARGET) $(OBJECTS) $(TEST_TARGET) $(TEST_OBJECTS)
